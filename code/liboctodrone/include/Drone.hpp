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
			Drone(CommMod* cm, double iX, double iY, double iZ, double maxSpeed, Environment* e);
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

			double getSpeed();

			double getAngle();

			bool hasFinishedMoving();
			
			double sense(std::string type);

		private:
			double oTime;
			bool alive = true;
			Direction dir;
			double maxSpeed;
			double ang = 0;

			Environment* env;
			double moveDR, moveSpd;
			void execute(std::string, double);
	};

#endif
