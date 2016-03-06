#ifndef EOW_DRONE_HPP
	#define EOW_DRONE_HPP

	#include <string>
	#include "Messageable.hpp"

	class CommMod;

	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		FORWARD,
		BACK
	};

	class Drone: public Messageable {
		public:
			Drone(CommMod* cm, double iX, double iY, double iZ, double maxSpeed, double sensorRadius, Environment* e);
			bool isAlive();
			void upkeep();

		protected:
			void kill();
			//clockwise
			void turn(double dAngle);
			//speed is in units/tick, with units being items on the ENV data map and a tick
			//being however long a single cycle takes, should do some thread stuff to synch
			//everything
			void move(Direction direction, double speed, double distance);

			//in all cases, angles are measured as y0 being forward, x0 and z0 being level
			//with the ground
			double getMaxSpeed();

			// The method responsible for continuing the correct job that the drone is doing
			void continueJob();

			int atLoc(Coord location);

			// Called when the drone is to measure a new area. Splits the area given up
			// into points that the drone needs to go to.
			void newArea(double x1, double y1, double x2, double y2, double height);

			double sense(std::string type);

		private:
			double oTime;
			bool alive = true;
			Direction dir;
			double maxSpeed;
			double ang = 0;

			Environment* env;
			double moveDR, moveSpd;

			double sensorRadius;

			// The queue that contains the remaining points to be visited.
			std::queue<Coord> remainingPoints;
			
	};

#endif
