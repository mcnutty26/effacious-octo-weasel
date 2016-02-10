#include "Drone.hpp"

#include <cmath>
#include "Messageable.hpp"

#define PI 3.14159265

Drone::Drone(CommMod* cm, double iX, double iY, double iZ, double maxSpeed, Environment* e)
:Messageable(cm, iX, iY, iZ)
{
	this->maxSpeed = maxSpeed;
	env = e;
}

void Drone::upkeep()
{
	if(moveDR <= 0)
	{
		moveDR = 0;
		return;
	}
	double radcon = PI/180;
	double distance = moveDR < moveSpd? moveDR:moveSpd;

	switch(dir)
	{
		case Direction::UP:
			zPos += distance;
			break;
		case Direction::DOWN:
			zPos -= distance;
			break;
		case Direction::LEFT:
			xPos += distance*sin((ang - 90)*radcon);
			yPos += distance*cos((ang - 90)*radcon);
			break;
		case Direction::RIGHT:
			xPos += distance*sin((ang + 90)*radcon);
			yPos += distance*cos((ang + 90)*radcon);
			break;
		case Direction::FORWARD:
			xPos += distance*sin((ang)*radcon);
			yPos += distance*cos((ang)*radcon);
			break;
		case Direction::BACK:
			xPos += distance*sin((ang + 180)*radcon);
			yPos += distance*cos((ang + 180)*radcon);
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
	return env->getData(type, xPos, yPos, zPos);
}
