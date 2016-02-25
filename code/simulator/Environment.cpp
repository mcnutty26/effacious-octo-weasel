#include "Environment.hpp"
#include "Messageable.hpp"

#include <cmath>
#include <iostream>
#include <thread>
#include <atomic>

std::atomic_flag lock_broadcast = ATOMIC_FLAG_INIT;

std::string passStr(std::string in)
{
	return in;
}

Environment::Environment(std::map<std::string, data_type> sensor_data, std::function <std::string(std::string)> nfun)
:noiseFun(nfun)
{
	data = sensor_data;
};

Environment::Environment(std::map<std::string, data_type> sensor_data)
{
	data = sensor_data;
	noiseFun = &passStr;
}

//should not be called by anything other than the main thread
void Environment::addData(std::string type, data_type d)
{
	data[type] = d;
}

//should not be called by anything other than the main thread
void Environment::addMessageable(Messageable* m)
{
	messageables.push_back(m);
}

void Environment::setBaseStation(BaseStation* b){
    baseStation = b;
}

//thread safe (I hope) may be a little slow though... meh, it'll be fine (again... I hope)
void Environment::broadcast(std::string message, double xOrigin, double yOrigin, double zOrigin, double range)
{
	std::string nMessage = noiseFun(message);
	while(lock_broadcast.test_and_set()){}
	for(auto m:messageables)
	{
		//if messageable is within range
		if(pow(m->getX() - xOrigin,2) + pow(m->getY() - yOrigin, 2) + pow(m->getZ() - zOrigin, 2) < range)
		{
			std::cout << m->getY() << "|" << yOrigin << std::endl;
			m->receive_message(nMessage);
		}
	}
	lock_broadcast.clear();
}

void Environment::run()
{
	std::vector<std::thread> threads;
	for(auto x : messageables)
	{
		threads.emplace_back(&Messageable::run, x);
		threads.emplace_back(&Messageable::runCommMod, x);
	}

	for(std::vector<std::thread>::size_type i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}
}

double Environment::getData(std::string type, double x, double y, double z)
{
	return data[type][(int)std::round(x)][(int)std::round(y)][(int)std::round(z)];
}
