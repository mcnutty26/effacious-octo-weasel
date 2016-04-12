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

#ifndef EOW_MESSAGEABLE_HPP
	#define EOW_MESSAGEABLE_HPP

	#include <string>
	#include <queue>

	#include "CommMod.hpp"
	#include "Message.hpp"

	class CommMod;

	struct Coord
	{
		double x, y, z;
	};

	class Messageable
	{
		public:
			Messageable(CommMod* cm, double xp, double yp, double zp);
			void send_message(Message* contents);
			Message* wait_for_message();
			void push_message(Message* contents);
			void receive_message(std::string contents);
			CommMod* get_comm_mod();

			double getX();
			double getY();
			double getZ();

			Coord getPosition();

			double getTime();

			//returns true if the message is consumed by the callback.
			//false otherwise.
			virtual bool message_callback(Message* message) = 0;

			bool getAlive();

			//to avoid weirdness
			void run_wrapper();

			//should terminate when the task is finished.
			virtual void run() = 0;

			void runCommMod();
		protected:
			std::queue<Message*> inQueue;
			CommMod* communicationsModule;

			Coord position;

		private:
			bool alive;
	};

#endif
