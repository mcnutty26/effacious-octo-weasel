#include "SensingBaseStation.hpp"
#include <iostream>
#include <Basic_message_addressed.hpp>




SensingBaseStation::SensingBaseStation(CommMod* cm, double xp, double yp, double zp, double areaX1, double areaY1, double areaX2, double areaY2) : BaseStation(cm, xp, yp, zp) {
	this->areaX1 = areaX1;
	this->areaX2 = areaX2;
	this->areaY1 = araeY1;
	this->areaY2 = areaY2;
}

void SensingBaseStation::run() {

	// Wait for a certain amount of time to discover number of drones
	// Drone IPs are hardcoded in for now
	droneIPs.insert("10.0.0.1");
	droneIPs.insert("10.0.0.2");
	int numDrones = 2;


	// Once the number of drones is known, distribute the area
	double x1s[numDrones];
	double y1s[numDrones];
	double x2s[numDrones];
	double y2s[numDrones];
	double xSize = (areaX2 - areaX1) / numDrones;
	for (int i = 0; i < numDrones; i++)
	{
		x1s[i] = (i * xSize) + areaX1;
		x2s[i] = ((i + 1) * xSize) + areaX1;
		y1s[i] = areaY1;
		y2s[i] = areaY2;
	}

	// broadcast messages to each drone so that they know which area they should be measuring
	for (int i = 0; i < numDrones; i++)
	{
		std::string message = std::string("NEWAREA=") + x1s[i] + "," + y1s[i] + "," + x2s[i] + "," + y2s[i];
		send_message(new Basic_message_addressed(message, dronesIP.at(i)));
	}

	std::cout << "Basestation thread ended" << std::endl;
}
