#ifndef EOW_PROGRAMS_SENSINGDRONE
	#define EOW_PROGRAMS_SENSINGDRONE

	#include <string>
	#include <Drone.hpp>
	#include <CommMod.hpp>
	#include <Message.hpp>

	typedef std::vector<std::vector<std::vector<double>>> data_type;

	class AodvComms: public Drone {
		public:
			AodvComms(CommMod*, double, double, double, double, Environment*, int, int*);
			bool message_callback(Message*);
			void run();

			// The method responsible for continuing the correct job that the drone is doing
			void continueJob();

			int atLoc(Coord location);

			// Called when the drone is to measure a new area. Splits the area given up
			// into points that the drone needs to go to.
			void newArea(double x1, double y1, double x2, double y2, double height);

		private:
			int m_task;
			int* m_flag;
			void quit();

			// The queue that contains the remaining points to be visited.
			std::queue<Coord> remainingPoints;
	};
#endif
