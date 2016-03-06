#include "BaseStation.hpp"

// TODO: remove
#include <iostream>

BaseStation::BaseStation(CommMod* cm, double xp, double yp, double zp, double areaX1, double areaY1, double areaX2, double areaY2): Messageable(cm, xp, yp, zp){

	// Wait for a certain amount of time to discover number of drones


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
		// TODO: remove
		std::cout << x1s[i] << x2s[i] << y1s[i] << y2s[i] << std::endl;

		// broadcast message...
	}

}
