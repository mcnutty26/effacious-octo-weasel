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

#include "SensingBaseStation.hpp"
#include <iostream>
#include <Basic_addressed_message.hpp>
#include <Basic_addressed.hpp>

SensingBaseStation::SensingBaseStation(CommMod* cm, double xp, double yp, double zp, double areaX1, double areaY1, double areaX2, double areaY2) : BaseStation(cm, xp, yp, zp) {
	this->areaX1 = areaX1;
	this->areaX2 = areaX2;
	this->areaY1 = areaY1;
	this->areaY2 = areaY2;
}

void SensingBaseStation::run() {

	// Wait for a certain amount of time to discover number of drones
	// Drone IPs are hardcoded in for now
	//droneIPs.push_back("10.0.0.1");
	//droneIPs.push_back("10.0.0.2");
	//int numDrones = 2;
	
	std::string message = std::string("BASEIP=");
	// Broadcast a message to other messagable
	send_message(new Basic_addressed_message(message, "255.255.255.255", ""));

	double startTime = getTime();
	double timeElapsed = 0;
	while (timeElapsed < 5000000)
	{
		// Perhaps replace this section with a function on the 
		// Messageble class. This was required because the 
		// wait_for_message function blocks.
		if (!inQueue.empty())
		{
			Message* message = inQueue.front();
			inQueue.pop();

			interpretMessage(message);
		}

		timeElapsed = getTime() - startTime;
	}

	int numDrones = droneIPs.size();
	std::cout << "Num Drones: " << numDrones << std::endl;

	// Once the number of drones is known, distribute the area
	double x1s[numDrones];
	double y1s[numDrones];
	double x2s[numDrones];
	double y2s[numDrones];
	double xSize = (areaX2 - areaX1) / numDrones;
	//std::cout << "xSize is " << xSize << std::endl;
	for (int i = 0; i < numDrones; i++)
	{
		x1s[i] = (i * xSize) + areaX1;
		x2s[i] = ((i + 1) * xSize) + areaX1;
		y1s[i] = areaY1;
		y2s[i] = areaY2;
		//std::cout << "Drone " << i << " area: (" << x1s[i] << ", " << y1s[i] << ", " << x2s[i] << ", " << y2s[i] << ")" << std::endl;
	}

	// broadcast messages to each drone so that they know which area they should be measuring
	for (int i = 0; i < numDrones; i++)
	{
		std::string message = std::string("NEWAREA=") + std::to_string(x1s[i]) + "," + std::to_string(y1s[i]) + "," + std::to_string(x2s[i]) + "," + std::to_string(y2s[i]);
		//std::cout << "BASESTATION: Sending area to drone " << droneIPs[i] << "(" << message << ")" << std::endl;
		send_message(new Basic_addressed_message(message, droneIPs.at(i), ""));
	}

	// Wait for messages from drones containing information
	bool done = false; // Will be true when all the data has been collected
	while (!done)
	{
		Basic_addressed_message* message = dynamic_cast<Basic_addressed_message*>(wait_for_message());
		interpretMessage(message);
	}

	std::cout << "Basestation thread ended" << std::endl;
}

bool SensingBaseStation::message_callback(Message* message) {
	(void) message;
	return false;
}

void SensingBaseStation::interpretMessage(Message* msg)
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
		valuesReversed.push_back(values[i]);
	}
	values = valuesReversed;

	/* Act on the message */
	if (valueName == "DATUM")
	{ // This message contains a data point
		std::string log_message = std::string(" Received point (") + values[0] + ", " + values[1] + ", " + values[2] + ", " + values[3] + " from drone " + message->get_source();
		log(log_message);
		//std::cout << "BASESTATION: Received point (" << values[0] << ", " << values[1] << ", " << values[2] << ") = " << values[3] << " from drone " << message->get_source() << std::endl;
	}
	else if (valueName == "DRONEIP")
	{ // This message contains a drone IP
		//std::cout << "BASESTATION: Drone IP discovered: ";
		//std::cout << message->get_source() << std::endl;
		droneIPs.push_back(message->get_source());
	}

}

void SensingBaseStation::log(std::string log_message)
{
	dynamic_cast<Basic_addressed*>(communicationsModule)->log(log_message);
}
