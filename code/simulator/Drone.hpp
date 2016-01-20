#ifndef EOW_DRONE_HPP
	#define EOW_DRONE_HPP

	#include <string>

	#include "Messageable.hpp"
	#include "CommMod.hpp"

	class Drone
	:protected Messageable
	{
		public:
			Drone(CommMod* cm, double iX, double iY, double iZ, double maxSpeed);

			double xAng, yAng, zAng = 0;

			void upkeep();

		protected:
			void turn(double dXAngle, double dYAngle, double dZAngle);
			//speed is in units/tick, with units being items on the ENV data map and a tick
			//being however long a single cycle takes, should do some thread stuff to synch
			//everything
			void moveForward(double speed, double distance);
			void moveUp(double speed, double distance);
			void moveDown(double speed, double distance);
			void moveLeft(double speed, double distance);
			void moveRight(double speed, double distance);
			void moveBack(double speed, double distance);

			//in all cases, angles are measured as y0 being forward, x0 and z0 being level
			//with the ground
			void moveAngle(double speed, double distance, double xAngle, double yAngle, double zAngle);
			double getMaxSpeed();

		private:
			double maxSpeed;

			double moveDR, moveSpd, moveXAng, moveYAng, moveZAng;
	};

#endif
