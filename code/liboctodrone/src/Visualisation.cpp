#include "Visualisation.hpp"

#include <atomic>

std::atomic_flag lock_vis = ATOMIC_FLAG_INIT;

bool running;

Element::Element(IMG img, int x, int y, int size, int steps)
{
	image = img;
	this->x = x;
	this->y = y;
	this->size = size;
	stepsLeft = steps;
}

bool Element::step()
{
	return !(--stepsLeft);
}

void Element::draw()
{
	//find the right image
	switch(image)
	{
		case IMG::DRONE:
			break;
		case IMG::STATION:
			break;
		case IMG::BCAST:
			break;
	}

	//draw the image at x, y with size "size"
}

void step()
{
	while(lock_vis.test_and_set()){}
	for(auto i = elements.begin(); i != elements.end(); ++i)
	{
		if(i->step())
		{
			i = elements.erase(i);
			--i;
		}
	}
	lock_vis.clear();
}

void visLoop()
{
	running = true;
	while(running)
	{
		while(lock_vis.test_and_set()){}
		for(auto i = elements.begin(); i != elements.end(); ++i)
		{
			i->draw();
		}
		lock_vis.clear();
	}
}

void visKill()
{
	running = false;
}

void pushDrone(int x, int y)
{
	elements.emplace_back(IMG::DRONE, x, y, 1, 1);
}

void pushBcast(int x, int y, int range)
{
	elements.emplace_back(IMG::BCAST, x, y, range, 2);
}

void pushBstation(int x, int y)
{
	elements.emplace_back(IMG::STATION, x, y, 1, -1);
}
