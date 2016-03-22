#include "Environment.hpp"
#include "Drone.hpp"
#include "BaseStation.hpp"

#include <cmath>
#include <thread>
#include <atomic>

std::atomic_flag lock_broadcast = ATOMIC_FLAG_INIT;

std::string passStr(std::string in)
{
	return in;
}

Environment::Environment(std::map<std::string, data_type> sensor_data, std::function <std::string(std::string)> nfun, double timestep)
:noiseFun(nfun)
{
	timeStep = timestep;
	data = sensor_data;
	baseStation = NULL;
};

Environment::Environment(std::map<std::string, data_type> sensor_data, double timestep)
{
	timeStep = timestep;
	data = sensor_data;
	noiseFun = &passStr;
	baseStation = NULL;
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
	for(auto m:drones)
	{
		//if messageable is within range
		if(pow(m->getX() - xOrigin,2) + pow(m->getY() - yOrigin, 2) + pow(m->getZ() - zOrigin, 2) < range && m->get_comm_mod() != caller)
		{
			m->receive_message(nMessage);
		}
	}
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
}

double Environment::getTime()
{
	return time(nullptr);
}

double Environment::getData(std::string type, double x, double y, double z)
{
	return data[type][(int)std::round(x)][(int)std::round(y)][(int)std::round(z)];
}
