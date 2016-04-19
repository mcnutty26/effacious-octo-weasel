#include "Visualisation.hpp"

//increase this if the broadcasts are too jagged for your liking, decrease it if
//everything lags
#define CIRCLE_STEPS 10

//don't change this... except to make it more accurate, if you want... but seriously
//bad things will happen
#define PI 3.14159265

#include <atomic>
#include <cmath>

#include <GL/gl.h>

std::vector<Element> elements;

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
			glBegin(GL_TRIANGLES);
				glVertex2f(x-5, y-5);
				glVertex2f(x, y + 5);
				glVertex2f(x + 5, y - 5);
			glEnd();
			break;
		case IMG::STATION:
			glBegin(GL_QUADS);
				glVertex2f(x - 5, y - 5);
				glVertex2f(x + 5, y - 5);
				glVertex2f(x + 5, y + 5);
				glVertex2f(x - 5, y + 5);
			glEnd();
			break;
		case IMG::BCAST:
			glBegin(GL_LINE_LOOP);
				double step = 2*PI/CIRCLE_STEPS
				for(i = 0; i < CIRCLE_STEPS; i++)
				{
					glVertex2f(size*cos(step*i) + x, size*sin(step*i) + y);
				}
			glEnd();
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
	elements.emplace_back(IMG::BCAST, x, y, range, 5);
}

void pushBstation(int x, int y)
{
	elements.emplace_back(IMG::STATION, x, y, 1, -1);
}
