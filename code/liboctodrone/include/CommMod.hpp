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

#ifndef EOW_COMM_MOD_HPP
	#define EOW_COMM_MOD_HPP

	#include <string>
	#include <queue>
	#include "Message.hpp"
	#include "Environment.hpp"
	#include "Messageable.hpp"

	class Environment;

	class CommMod
	{
		public:
			CommMod(Environment* env);
			void set_messageable(Messageable* msg);
			void broadcast(std::string message, double xPos, double yPos, double zPos, double range);
			void broadcast(Message* message, double xPos, double yPos, double zPos, double range);
			void push_out_message(Message* message);
			void push_in_message(std::string message);
			void pass_message(Message* message);

			//to avoid weirdness
			void comm_function_wrapper();
			///Main loop which must be defined by communications implementations
			virtual void comm_function() = 0;

			bool getAlive();

			double getTime();
		protected:
			///the queue of messages to be sent
			std::queue<Message*> outQueue;
			
			///the queue of received messages waiting for collection by the messageable
			std::queue<std::string> inQueue;

			///Reference to the simulation environment
			Environment* environment;

			///Reference to the associated messageable
			Messageable* messageable;

		private:
			bool alive;
	};

#endif
