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

	double xDistance = distance*sin(moveYAng*radCon);
	double yDistance = distance*sin(moveZAngle*radCon);
	double zDistance = distance*sin(moveXAngle*radCon);

	xPos += xDistance;
	yPos += yDistance;
	zPos += zDistance;

	moveDR -= distance;
}

void Drone::moveForward(double speed, double distance)
{
	moveAngle(speed, distance, xAng, yAng, zAng);
}

void Drone::moveUp(double speed, double distance)
{
	moveAngle(speed, distance, xAng, yAng, zAng);
}

void Drone::moveDown(double speed, double distance)
{
	moveAngle(speed, distance, xAng, yAng, zAng);
}

void Drone::moveLeft(double speed, double distance)
{
	moveAngle(speed, distance, xAng, yAng, zAng);
}

void Drone::moveRight(double speed, double distance)
{
	moveAngle(speed, distance, xAng, yAng, zAng);
}

void Drone::moveBack(double speed, double distance)
{
	moveAngle(speed, distance, xAng+180, yAng, zAng);
}


