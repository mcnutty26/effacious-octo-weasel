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

	class Drone: protected Messageable {
		public:
			Drone(CommMod*, double, double, double, double);
			void upkeep();

		protected:
			//clockwise
			void turn(double dAngle);
			//speed is in units/tick, with units being items on the ENV data map and a tick
			//being however long a single cycle takes, should do some thread stuff to synch
			//everything
			void move(Direction direction, double speed, double distance);

			//in all cases, angles are measured as y0 being forward, x0 and z0 being level
			//with the ground
			double getMaxSpeed();

		private:
			Direction dir;
			double maxSpeed;
			double ang = 0;

			double moveDR, moveSpd;
			
	};

#endif
