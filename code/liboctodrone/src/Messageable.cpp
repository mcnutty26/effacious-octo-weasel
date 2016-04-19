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

#include "Messageable.hpp"

Messageable::Messageable(CommMod* cm, double xp, double yp, double zp)
{
	communicationsModule = cm;

	position.x = xp;
	position.y = yp;
	position.z = zp;
}

double Messageable::getX()
{
	return position.x;
}

double Messageable::getY()
{
	return position.y;
}

double Messageable::getZ()
{
	return position.z;
}

Coord Messageable::getPosition()
{
	return position;
}

double Messageable::getTime()
{
	return communicationsModule->getTime();
}

void Messageable::send_message(Message* contents)
{
	communicationsModule->push_out_message(contents);
}

void Messageable::receive_message(std::string contents)
{
	communicationsModule->push_in_message(contents);
}

Message* Messageable::wait_for_message()
{
	while(inQueue.empty()){}
	Message* message = inQueue.front();
	inQueue.pop();
	return message;
}

void Messageable::push_message(Message* contents)
{
	if(!message_callback(contents))
	{
		inQueue.push(contents);
	}
}

bool Messageable::getAlive()
{
	return alive | communicationsModule->getAlive();
}

void Messageable::run_wrapper()
{
	alive = true;
	run();
	alive = false;
}

void Messageable::runCommMod()
{
	communicationsModule->set_messageable(this);
	communicationsModule->comm_function_wrapper();
}

CommMod* Messageable::get_comm_mod(){
	return communicationsModule;
}
