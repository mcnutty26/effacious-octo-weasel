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

#ifndef EOW_PROGRAMS_SENSINGDRONE
	#define EOW_PROGRAMS_SENSINGDRONE

	#include <string>
	#include <Drone.hpp>
	#include <CommMod.hpp>
	#include <Message.hpp>

	typedef std::vector<std::vector<std::vector<double>>> data_type;

	class SensingDrone: public Drone {
		public:
			SensingDrone(CommMod*, double, double, double, double, double, Environment*, bool /*, int, int* */);
			bool message_callback(Message*);
			void run();


		private:
			// The method responsible for continuing the correct job that the drone is doing
			void continueJob();

			void interpretMessage(Message* message);
			void sendDataPoint(double, double, double, double);

			int atLoc(Coord location);

			// Called when the drone is to measure a new area. Splits the area given up
			// into points that the drone needs to go to.
			void newArea(double x1, double y1, double x2, double y2, double height);

			int m_task;
			int* m_flag;
			void quit();

			double sensorRadius;
			// The drone with the lower routing priority will 
			// be forced to wait when a possible collision is detected
			int routingPriority;

			double lastTime;
			double waitTimer;
			bool waiting;

			// The queue that contains the remaining points to be visited.
			std::queue<Coord> remainingPoints;

			bool sink_node;

			std::string baseStationIP;
			std::vector<std::string> droneIPs;

			bool givenArea;
	};
#endif
