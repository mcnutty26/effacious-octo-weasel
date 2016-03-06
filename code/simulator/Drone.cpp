#include "Drone.hpp"

#include <cmath>
#include "Messageable.hpp"

// TODO: remove
#include <iostream>

#define PI 3.14159265

Drone::Drone(CommMod* cm, double iX, double iY, double iZ, double maxSpeed, Environment* e)
:Messageable(cm, iX, iY, iZ)
{
	this->maxSpeed = maxSpeed;
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
