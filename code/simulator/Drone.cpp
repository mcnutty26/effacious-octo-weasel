#include "Drone.hpp"

#include <cmath>

#define PI 3.14159265

void Drone::upkeep()
{
	if(moveDR <= 0)
	{
		moveDR = 0;
		return;
	}
	double radCon = PI/180;
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
			break;
		case Direction::RIGHT:
			xPos += distance*sin((ang + 90)*radcon);
			break;
		case Direction::FORWARD:
			xPos += distance*sin((ang)*radcon);
			break;
		case Direction::BACK:
			xPos += distance*sin((ang + 180)*radcon);
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


void Drone::move(Direction direction, double speed, double distance);
{
	dir = direction;
	moveDR = distance;
	moveSpd = speed;
}
