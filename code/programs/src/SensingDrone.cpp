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

#include "SensingDrone.hpp"
#include <iostream>
#include <Basic_message.hpp>
#include <Basic_addressed_message.hpp>
#include <chrono>
#include <thread>
#include <cmath>

#define PI 3.14159265

SensingDrone::SensingDrone(CommMod* cm, double xp, double yp, double zp, double speed, double sensorRadius, Environment* env, bool sink/*, int task, int* flag*/): Drone(cm, xp, yp, zp, speed, env){
	this->sensorRadius = sensorRadius;
	
	sink_node = sink;

	/*
	m_task = task;
	m_flag = flag;
	*/
	
};

bool SensingDrone::message_callback(Message*){
    return false;
}

void SensingDrone::run(){
	/*
	if (sink_node){
		std::cout << "Sink waiting for message" << std::endl;
		std::cout << wait_for_message()->to_string() << std::endl;
		send_message(new Basic_message("KILL"));
	} else {
		std::cout << "Source sending message" << std::endl;
		send_message(new Basic_message("TEST MESSAGE PLEASE IGNORE"));
		send_message(new Basic_message("KILL"));
	}
	*/

	// Wait for message from base station to begin
	// Discover other IPs of drones and base station
	baseStationIP = "10.0.0.255"; // Hardcoded for now
	

	while (isAlive())
	{
		if (!remainingPoints.empty())
			continueJob();
		else
		{
			Basic_addressed_message* message = dynamic_cast<Basic_addressed_message*>(wait_for_message());
			// Will the message be lost if it is not from the basestation?
			if (message->get_destination() == baseStationIP)
			{
				std::string str = message->get_message();
				std::cout << "DRONE: Sensing on area:";
				std::cout << str << std::endl;

				// Needs actual values
				//newArea(1.0, 1.0, 5.0, 5.0, 1.0);
			}
			
		}
	}

	/*
	switch(m_task){
		case 0:
			std::cout << "Sink waiting for message" << std::endl;
			std::cout << wait_for_message()->to_string() << std::endl;
			*m_flag = 1;
			break;
		case 1:
			std::cout << "Source sending message" << std::endl;
			send_message(new Basic_addressed_message("TEST MESSAGE PLEASE IGNORE", "10.0.0.1"));
			break;
		case -1:
			while (*m_flag != 1){
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
	}
	send_message(new Basic_message("KILL"));
	*/
}

void SensingDrone::continueJob()
{
	if (hasFinishedMoving())
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
				dAngle -= getAngle();

				double distance = sqrt((dx * dx) + (dy * dy));

				turn(dAngle);
				move(Direction::FORWARD, getMaxSpeed(), distance);

			}
			else
			{
				double distance = 0.0;
				Direction direction;
				if (position.z < target.z)
				{
					direction = Direction::UP;
					distance = target.z - position.z;
				}
				else
				{
					direction = Direction::DOWN;
					distance = position.z - target.z;
				}
				move(direction, getMaxSpeed(), distance);
			}
		}
	}
}

int SensingDrone::atLoc(Coord location)
{
	// This will need to be changed to incorporate a 
	// degree of error with the GPS
	return (position.x == location.x && position.y == location.y && position.z == location.z);
}

// For now, there is no intelligence as to what order the points
// are put into the queue.
void SensingDrone::newArea(double x1, double y1, double x2, double y2, double height)
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

/*


*/
