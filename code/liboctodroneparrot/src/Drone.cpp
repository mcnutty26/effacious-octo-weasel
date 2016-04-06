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

///Modified implementation of Drone for the Parrot AR 2 drone

#include "Drone.hpp"
#include <cmath>
#include "Messageable.hpp"
#include <iostream>

#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define PI 3.14159265

Drone::Drone(CommMod* cm, double iX, double iY, double iZ, double maxSpeed, Environment* e)
:Messageable(cm, iX, iY, iZ)
{
	this->maxSpeed = maxSpeed;
	env = e;
	execute("TAKEOFF", 0.0);
}

bool Drone::isAlive()
{
	return alive;
}

void Drone::kill()
{
	alive = false;
	execute("LAND", 0.0);
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
			execute("UP", 0.5);
			break;
		case Direction::DOWN:
			execute("DOWN", 0.5);
			break;
		case Direction::LEFT:
			execute("LEFT", 0.5);
			break;
		case Direction::RIGHT:
			execute("RIGHT", 0.5);
			break;
		case Direction::FORWARD:
			execute("FRONT", 0.5);
			break;
		case Direction::BACK:
			execute("BACK", 0.5);
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

///Takes a command and sends it to the node server which is connected to the drone
void Drone::execute(std::string command, double arg){
	//set up connection variables
	#define SOCK_PATH "parrot.sock"
	int s, t, len;
	struct sockaddr_un remote;
	char str[100];

	//prepare the request as a c string
	strcat(str, command.c_str());
	strcat(str, ";");
	strcat(str, std::to_string(arg).c_str());

	//get a handle for the socket
	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		std::cout << "Error getting address of socket " << SOCK_PATH << std::endl;
		exit(1);
	}

	//connect to the socket
	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH);
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (connect(s, (struct sockaddr *)&remote, len) == -1) {
		std::cout << "Error connecting to socket " << SOCK_PATH << std::endl;
		exit(1);
	}

	//send the request
	if (send(s, str, strlen(str), 0) == -1) {
		std::cout << "Error sending via socket" << SOCK_PATH << std::endl;
		exit(1);
	}

	//close the connection
	close(s);
}
