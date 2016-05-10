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
#include <Basic_addressed.hpp>
#include <chrono>
#include <thread>
#include <cmath>

#define PI 3.14159265

#define PING_FREQ 500000

SensingDrone::SensingDrone(CommMod* cm, double xp, double yp, double zp, double speed, double sensorRadius, Environment* env, bool sink): Drone(cm, xp, yp, zp, speed, env){
	this->sensorRadius = sensorRadius;
	
	sink_node = sink;

	routingPriority = 0;
	
};

bool SensingDrone::message_callback(Message*){
    return false;
}

void SensingDrone::run(){

	// Wait for message from base station to begin
	// Discover other IPs of drones and base station
	//baseStationIP = "10.0.0.255"; // Hardcoded for now
	
	//std::cout << "Drone thread started." << std::endl;

	std::string message = std::string("DRONEIP=");
	// Broadcast a message to the other messageables
	send_message(new Basic_addressed_message(message, "255.255.255.255", ""));
	

	//double startTime = getTime();
	//double timeElapsed = 0;
	baseStationIP = "";
	while (baseStationIP == "")
	{
		if (!inQueue.empty())
		{
			Message* message = inQueue.front();
			inQueue.pop();

			interpretMessage(message);
		}
		//timeElapsed = getTime() - startTime;
	}
	//std::cout << "The Basestation IP is: " << baseStationIP << std::endl;

	givenArea = false;

	while (isAlive())
	{
		// Broadcast the drone's location
		std::string message = std::string("LOC=") + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) + "," + std::to_string(getAngle()) + "," + std::to_string(getMaxSpeed()) + "," + std::to_string(routingPriority);
		send_message(new Basic_addressed_message(message, "255.255.255.255", ""));

		if (waitTimer > 0)
		{
			double time = getTime();
			waitTimer -= time - lastTime;
			lastTime = time;
		}

		if (!remainingPoints.empty())
		{
			if (waitTimer <= 0)
				continueJob();
		}
		else
		{
			if (givenArea)
			{
				kill();
				break;
			}
			//std::cout << "DRONE: waiting for new area" << std::endl;
			log(" waiting for new area");

			while (!givenArea)
			{
				Basic_addressed_message* message = dynamic_cast<Basic_addressed_message*>(wait_for_message());
				interpretMessage(message);
			}
			
		}
	}

	//std::cout << "Drone Thread Ending" << std::endl;
	log("Exiting");

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
		//std::cout << "Drone has finished moving and is at (" << position.x << ", " << position.y << ", " << position.z << ") and the target is (" << target.x << ", " << target.y << ", " << target.z << ")" << std::endl;
		if (atLoc(target))
		{
			// the sense function segmentation faults
			//double reading = sense("Test");
			remainingPoints.pop();
			//std::cout << "Sensing at (" << position.x << ", " << position.y << ", " << position.z << ") - " << remainingPoints.size() << " remaining points" << std::endl;
			sendDataPoint(position.x, position.y, position.z, 42.0);
		}
		else
		{
			//std::cout << "Finding a route to (" << target.x << ", " << target.y << ", " << target.z << ")" <<  std::endl;
			if (position.x != target.x || position.y != target.y)
			{
				double dx = target.x - position.x;
				double dy = target.y - position.y;
				
				double dAngle = atan2(dx, dy) * 180 / PI;
				dAngle -= getAngle();
				if (dAngle >= 360)
					dAngle -= 360;
				else if (dAngle <= -360)
					dAngle += 360;

				double distance = sqrt((dx * dx) + (dy * dy));

				//std::cout << "Turning " << dAngle << std::endl;
				turn(dAngle);
				//std::cout << "Moving Direction::FORWARD, " << getMaxSpeed() << ", " << distance << std::endl;
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
				//std::cout << "Moving ";
				//if (direction == Direction::DOWN) std::cout << "DOWN";
				//else std::cout << "UP";
				//std::cout << ", " << getMaxSpeed() << ", " << distance << std::endl;
				move(direction, getMaxSpeed(), distance);
			}
		}
	}
}

void SensingDrone::sendDataPoint(double x, double y, double z, double datum)
{
	std::string message = std::string("DATUM=") + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "," + std::to_string(datum);
	//std::cout << "DRONE: Sending data point: " << message << std::endl;
	//std::cout << "DRONE: sending message to " << baseStationIP << std::endl;
	send_message(new Basic_addressed_message(message, "10.0.0.255", ""));
}

void SensingDrone::interpretMessage(Message* msg)
{
	Basic_addressed_message* message = dynamic_cast<Basic_addressed_message*>(msg);

	/* Decode the Message */
	std::string msgstr = message->get_message();
	int equalsLocation = msgstr.find_first_of('=');
	std::string valueName = msgstr.substr(0, equalsLocation);

	std::vector<std::string> values;

	std::size_t i = equalsLocation + 1;
	int iLast = i;
	for (i = iLast; i < msgstr.size(); i++)
	{
		if (msgstr[i] == ',')
		{
			values.push_back(msgstr.substr(iLast, i - iLast));
			iLast = i + 1;
		}
	}
	values.push_back(msgstr.substr(iLast, i - iLast));

	std::vector<std::string> valuesReversed;
	for (i = 0; i < values.size(); i++)
	{
		valuesReversed.push_back(values.at(i));
	}
	values = valuesReversed;

	/* Act on the msgstr */
	if (valueName == "NEWAREA" && message->get_source() == baseStationIP)
	{
		//std::cout << "DRONE: Sensing on area: ";
		//std::cout << values.at(0) << ", " << values.at(1) << ", " << values.at(2) << ", " << values.at(3)  << std::endl;
		log(msgstr);

		newArea(std::stod(values[0]), std::stod(values[1]), std::stod(values[2]), std::stod(values[3]), 1.0);
		givenArea = true;
	}
	else if (valueName == "BASEIP")
	{
		baseStationIP = message->get_source();
	}
	else if (valueName == "DRONEIP")
	{
		droneIPs.push_back(message->get_source());
	}
	else if (valueName == "LOC")
	{ // This is a location ping from another drone
		// The perceived size of a drone (hopefully much bigger than the drone itself)

		//std::cout << "DRONE: Received Location ping: ";
		/*
		for (auto v : values)
		{
			std::cout << v << ", ";
		}
		std::cout << std::endl;
		*/

		double collisionDiameter = 2.0;

		double radcon = PI/180;


		if (stoi(values[5]) > routingPriority) // if we have lower priority
		{
			// 1 is this drone, 2 is the other drone
			double dx1 = PING_FREQ * 2 * getMaxSpeed() * sin(getAngle() * radcon);
			double dy1 = PING_FREQ * 2 * getMaxSpeed() * cos(getAngle() * radcon);
	
			double dx2 = PING_FREQ * 2 * stod(values[4]) * sin(stod(values[3]) * radcon);
			double dy2 = PING_FREQ * 2 * stod(values[4]) * cos(stod(values[3]) * radcon);

			double x1, y1, x2, y2;

			bool collision = false;
			// Incrementally check for potential collision along immediate
			// route. Calculating exact point of collision unnecessary.
			for (int i = 0; i < 5; i++)
			{
				x1 = position.x + dx1 * i;
				y1 = position.y + dy1 * i;
				x2 = stod(values[0]) + dx2 * i;
				y2 = stod(values[1]) + dy2 * i;
	
				if ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) < collisionDiameter * collisionDiameter)
				{
					// This drone will be unsafely close to the 
					// other drone by the next ping
					collision = true;
				}
			}
			if (collision)
			{
				waiting = true;
				move(Direction::DOWN, getMaxSpeed(), 1);
				waitTimer = PING_FREQ * 2;
				std::string log_message = std::string("Potential collision detected between ") + message->get_source() + " and " + message->get_destination();
				log(log_message);
				//std::cout << "Potential collision detected between " << message->get_source() << " and " << message->get_destination() << std::endl;
			}
		}


	}

}

// Test to see if the drone is at the given location.
// The accuracy is dependent on the sensor radius - 
// the larger the radius, the larger the margin of 
// allowed error
int SensingDrone::atLoc(Coord location)
{
	double error = sensorRadius; // Currently a sizeable error
	return (position.x < location.x + error && position.x > location.x - error && position.y < location.y + error && position.y > location.y - error && position.z < location.z + error && position.z > location.z - error);
}

// Take a rectangular area and split it into a vector of points.
// The ordering is done so that the drone will be moving up and 
// down the columns.
void SensingDrone::newArea(double x1, double y1, double x2, double y2, double height)
{
	double x, y, yAdjusted;
	double sensorDiameter = sensorRadius * 2.0f;
	int oddCol = 0;
	for (x = x1; x < x2; x += sensorDiameter)
	{
		for (y = y1; y < y2; y += sensorDiameter)
		{
			if (oddCol)
				yAdjusted = y2 - y;
			else
				yAdjusted = y;

			Coord coord;
			coord.x = x;
			coord.y = yAdjusted;
			coord.z = height;
			remainingPoints.push(coord);
		}
		oddCol = 1 - oddCol;
	}

	// Print off the area for debug:
	/*
	std::cout << "Drone Points:" << std::endl;
	Coord c;
	while (!remainingPoints.empty())
	{
		c = remainingPoints.front();
		std::cout << "(" << c.x << "," << c.y << "),"; 
		remainingPoints.pop();
	}
	std::cout << std::endl;
	*/
}

void SensingDrone::log(std::string log_message)
{
	dynamic_cast<Basic_addressed*>(communicationsModule)->log(log_message);
}

/*
void Basic_addressed::log(std::string log_message){
	while (lock->test_and_set()){}
	std::string ip_address = dynamic_cast<Basic_addressed*>(communicationsModule)->getIPAdress();
	std::cout << "basic_addressed@" << ip_address << ": " << log_message << std::endl;
	lock->clear();
}
*/

