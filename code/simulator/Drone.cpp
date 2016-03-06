#include "Drone.hpp"

#include <cmath>
#include "Messageable.hpp"

// TODO: remove
#include <iostream>

#define PI 3.14159265

Drone::Drone(CommMod* cm, double iX, double iY, double iZ, double maxSpeed, double sensorRadius, Environment* e)
:Messageable(cm, iX, iY, iZ)
{
	this->maxSpeed = maxSpeed;
	this->sensorRadius = sensorRadius;
	env = e;
}

bool Drone::isAlive()
{
	return alive;
}

void Drone::kill()
{
	alive = false;
}

void Drone::upkeep()
{
	double time = getTime();
	double dTime = time - oTime;
	oTime = time;
	if(moveDR <= 0)
	{
		moveDR = 0;
		return;
	}
	double radcon = PI/180;
	double distance = moveDR < moveSpd*dTime? moveDR:moveSpd*dTime;

	switch(dir)
	{
		case Direction::UP:
			position.z += distance;
			break;
		case Direction::DOWN:
			position.z -= distance;
			break;
		case Direction::LEFT:
			position.x += distance*sin((ang - 90)*radcon);
			position.y += distance*cos((ang - 90)*radcon);
			break;
		case Direction::RIGHT:
			position.x += distance*sin((ang + 90)*radcon);
			position.y += distance*cos((ang + 90)*radcon);
			break;
		case Direction::FORWARD:
			position.x += distance*sin((ang)*radcon);
			position.y += distance*cos((ang)*radcon);
			break;
		case Direction::BACK:
			position.x += distance*sin((ang + 180)*radcon);
			position.y += distance*cos((ang + 180)*radcon);
			break;
	}

	if (!remainingPoints.empty())
		continueJob();
	else
	{
		// Wait for a new broadcast with information for a new area...
	}

}

void Drone::continueJob()
{
	if (moveDR == 0)
	{
		Coord target = remainingPoints.front();
		if (atLoc(target))
		{
			double reading = sense("Test");
			std::cout << "Reading at (" << position.x << ", " << position.y << ", " << position.z << ") is " << reading << std::endl;
			remainingPoints.pop();
		}
		else
		{
			if (position.x != target.x || position.y != target.y)
			{
				double dx = target.x - position.x;
				double dy = target.y - position.y;

				double dAngle = atan2(dy, dx) * 180 / PI;
				dAngle -= ang;

				double distance = sqrt((dx * dx) + (dy * dy));

				turn(dAngle);
				move(Direction::FORWARD, maxSpeed, distance);

			}
			else
			{
				double distance = 0.0;
				if (position.z < target.z)
				{
					dir = Direction::UP;
					distance = target.z - position.z;
				}
				else
				{
					dir = Direction::DOWN;
					distance = position.z - target.z;
				}
				move(dir, maxSpeed, distance);
			}
		}
	}
}

int Drone::atLoc(Coord location)
{
	// This will need to be changed to incorporate a 
	// degree of error with the GPS
	return (position.x == location.x && position.y == location.y && position.z == location.z);
}

void Drone::turn(double dAngle)
{
	ang += dAngle;
	if(ang > 360)
	{
		ang -= 360;
	}
}

void Drone::move(Direction direction, double speed, double distance)
{
	dir = direction;
	moveDR = distance;
	moveSpd = speed;
}

double Drone::sense(std::string type)
{
	return env->getData(type, position.x, position.y, position.z);
}

// For now, there is no intelligence as to what order the points
// are put into the queue.
void Drone::newArea(double x1, double y1, double x2, double y2, double height)
{
	double x, y;
	double sensorDiameter = sensorRadius * 2.0f;
	for (x = x1; x < x2; x += sensorDiameter)
	{
		for (y = y1; y < y2; y += sensorDiameter)
		{
			Coord coord;
			coord.x = x;
			coord.y = y;
			coord.z = height;
			remainingPoints.push(coord);
		}
	}
}
