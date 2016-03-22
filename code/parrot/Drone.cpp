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

bool Drone::isAlive()
{
	return alive;
}

void Drone::kill()
{
	alive = false;
	system("node ../../parrot/js/parrot.js LAND");
}

void Drone::upkeep()
{
	double time = getTime();
	//double dTime = time - oTime;
	oTime = time;
	if(moveDR <= 0)
	{
		moveDR = 0;
		return;
	}
	//double radcon = PI/180;
	//double distance = moveDR < moveSpd*dTime? moveDR:moveSpd*dTime;

	switch(dir)
	{
		case Direction::UP:
			system("node ../../parrot/js/parrot.js UP 0.5");
			break;
		case Direction::DOWN:
			system("node ../../parrot/js/parrot.js DOWN 0.5");
			break;
		case Direction::LEFT:
			system("node ../../parrot/js/parrot.js LEFT 0.5");
			break;
		case Direction::RIGHT:
			system("node ../../parrot/js/parrot.js RIGHT 0.5");
			break;
		case Direction::FORWARD:
			system("node ../../parrot/js/parrot.js FRONT 0.5");
			break;
		case Direction::BACK:
			system("node ../../parrot/js/parrot.js BACK 0.5");
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
