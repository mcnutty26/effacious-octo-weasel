/*
This file is part of octoDrone.

octoDrone is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

octoDrone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with octoDrone.  If not, see <http://www.gnu.org/licenses/>.
*/

///Modified implementation of Environment for the Parrot AR 2 drone

#include "Environment.hpp"
#include "Drone.hpp"
#include "BaseStation.hpp"

#include <cmath>
#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>
#include <stdlib.h>

std::atomic_flag lock_broadcast = ATOMIC_FLAG_INIT;
FILE* node_server;

std::string passStr(std::string in)
{
	return in;
}

///Starts the node server which connects to the drone
void startNode(){
	//start the node server
	node_server = popen("node ../liboctodroneparrot/src/js/parrot.js", "w");
	if (!node_server){
		std::cout << "Error starting node server" << std::endl;
		exit(1);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

Environment::Environment(std::map<std::string, data_type> sensor_data, std::function <std::string(std::string)> nfun, double timestep)
:noiseFun(nfun)
{
	timeStep = timestep;
	data = sensor_data;
	baseStation = NULL;
	startNode();
};

Environment::Environment(std::map<std::string, data_type> sensor_data, double timestep)
{
	timeStep = timestep;
	data = sensor_data;
	noiseFun = &passStr;
	baseStation = NULL;
	startNode();
}

//should not be called by anything other than the main thread
void Environment::addData(std::string type, data_type d)
{
	data[type] = d;
}

//should not be called by anything other than the main thread
void Environment::addDrone(Drone* m)
{
	drones.push_back(m);
}

void Environment::setBaseStation(BaseStation* b){
    baseStation = b;
}

//thread safe (I hope) may be a little slow though... meh, it'll be fine (again... I hope)
void Environment::broadcast(std::string message, double xOrigin, double yOrigin, double zOrigin, double range, CommMod* caller)
{
	std::string nMessage = noiseFun(message);
	while(lock_broadcast.test_and_set()){}

	lock_broadcast.clear();
}

bool allRunning(std::vector<std::thread>* threads)
{
	bool running = false;
	for(auto x = threads->begin(); x != threads->end(); ++x)
	{
		running |= x->joinable();
	}
	return running;
}

void Environment::run()
{
	std::vector<std::thread> threads;
	for(auto x: drones)
	{
		threads.emplace_back(&Drone::run, x);
		threads.emplace_back(&Drone::runCommMod, x);
	}

	if (baseStation != NULL)
	{
		threads.emplace_back(&BaseStation::run, baseStation);
		threads.emplace_back(&BaseStation::runCommMod, baseStation);
	}

	while(allRunning(&threads))
	{
		for(auto x: drones)
		{
			if(x->isAlive())
			{
				x->upkeep();
			}
		}
	}

	for(std::vector<std::thread>::size_type i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}

	//shut down the node server
	if (pclose(node_server) != 0){
		std::cout << "Error shutting down node server" << std::endl;
		exit(1);
	}
}

double Environment::getTime()
{
	return time(nullptr);
}

double Environment::getData(std::string type, double x, double y, double z)
{
	return data[type][(int)std::round(x)][(int)std::round(y)][(int)std::round(z)];
}
