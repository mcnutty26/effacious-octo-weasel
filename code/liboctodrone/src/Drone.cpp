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

double Drone::getMaxSpeed()
{
	return maxSpeed;
}

double Drone::getAngle()
{
	return ang;
}

bool Drone::hasFinishedMoving()
{
	return (moveDR == 0);
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
