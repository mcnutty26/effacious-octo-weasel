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

#include "Environment.hpp"
#include "Drone.hpp"
#include "BaseStation.hpp"
#include "Visualisation.hpp"

#include <cmath>
#include <thread>
#include <atomic>
#include <iostream>

std::atomic_flag lock_broadcast = ATOMIC_FLAG_INIT;

std::string passStr(std::string in)
{
	return in;
}

Environment::Environment(std::map<std::string, data_type> sensor_data, std::function <std::string(std::string)> nfun, double timestep, bool visualise)
:noiseFun(nfun)
{
	timeStep = timestep;
	data = sensor_data;
	baseStation = NULL;
	this->visualise = visualise;
}

Environment::Environment(std::map<std::string, data_type> sensor_data, std::function <std::string(std::string)> nfun, double timestep)
:Environment(sensor_data, nfun, timestep, false)
{}

Environment::Environment(std::map<std::string, data_type> sensor_data, double timestep, bool visualise)
{
	timeStep = timestep;
	data = sensor_data;
	noiseFun = &passStr;
	baseStation = NULL;
	this->visualise = visualise;
}

Environment::Environment(std::map<std::string, data_type> sensor_data, double timestep)
:Environment(sensor_data, timestep, false)
{}

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

//should not be called by anything other than the main thread
void Environment::setBaseStation(BaseStation* b){
    baseStation = b;
}

//thread safe (I hope) may be a little slow though... meh, it'll be fine (again... I hope)
void Environment::broadcast(std::string message, double xOrigin, double yOrigin, double zOrigin, double range, CommMod* caller)
{
	if(visualise)
	{
		pushBcast((int) xOrigin, (int) yOrigin, range);
	}

	std::string nMessage = noiseFun(message);
	while(lock_broadcast.test_and_set()){}
	for(auto m:drones)
	{
		//if messageable is within range
		if(pow(m->getX() - xOrigin,2) + pow(m->getY() - yOrigin, 2) + pow(m->getZ() - zOrigin, 2) < range && m->get_comm_mod() != caller)
		{
			m->receive_message(nMessage);
		}
	}
	// For the basestation
	if(pow(baseStation->getX() - xOrigin,2) + pow(baseStation->getY() - yOrigin, 2) + pow(baseStation->getZ() - zOrigin, 2) < range && baseStation->get_comm_mod() != caller)
	{
		baseStation->receive_message(nMessage);
	}

	lock_broadcast.clear();
}

bool allRunning(std::vector<Drone*>* drones)
{
	bool running = false;

	for(auto x = drones->begin(); x != drones->end(); ++x)
	{
		running |= (*x)->getAlive();
	}
	return running;
}

void Environment::run()
{
	if (baseStation == nullptr){
		std::cout << "error@environment: no base station" << std::endl;
		exit(1);
	}

	std::vector<std::thread> threads;
	for(auto x: drones)
	{
		threads.emplace_back(&Drone::run_wrapper, x);
		threads.emplace_back(&Drone::runCommMod, x);
	}

	if (baseStation != NULL)
	{
		threads.emplace_back(&BaseStation::run_wrapper, baseStation);
		threads.emplace_back(&BaseStation::runCommMod, baseStation);
	}

	while(allRunning(&drones) || baseStation->getAlive())
	{
		for(auto x: drones)
		{
			if(x->isAlive())
			{
				x->upkeep(visualise);
			}
		}

		timeElapsed += timeStep;
	}

	for(std::vector<std::thread>::size_type i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}
}

double Environment::getTime()
{
	return timeElapsed;
}

double Environment::getData(std::string type, double x, double y, double z)
{
	return data[type][(int)std::round(x)][(int)std::round(y)][(int)std::round(z)];
}
