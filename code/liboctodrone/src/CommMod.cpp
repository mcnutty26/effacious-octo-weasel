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

///Base class for communication algorithm implementations

#include "CommMod.hpp"

CommMod::CommMod(Environment* env)
{
	environment = env;
}

bool CommMod::getAlive()
{
	return alive;
}

void CommMod::comm_function_wrapper()
{
	alive = true;
	comm_function();
	alive = false;
}

///Passes a message to the environment for transmission
void CommMod::broadcast(Message* message, double xPos, double yPos, double zPos, double range)
{
	environment->broadcast(message->to_string(), xPos, yPos, zPos, range, this);
}

///Passes a message to the environment for transmission
void CommMod::broadcast(std::string message, double xPos, double yPos, double zPos, double range)
{
	environment->broadcast(message, xPos, yPos, zPos, range, this);
}

///Called by a messagable to receive a message
void CommMod::push_in_message(std::string message)
{
	inQueue.push(message);
}

///Called by a messagable to send a message
void CommMod::push_out_message(Message* message)
{
	outQueue.push(message);
}

void CommMod::pass_message(Message* message)
{
	messageable->push_message(message);
}

///Set the messageble associated with this communications module
void CommMod::set_messageable(Messageable* msg)
{
	messageable = msg;
}

///Get the time from the environment
double CommMod::getTime()
{
	return environment->getTime();
}
