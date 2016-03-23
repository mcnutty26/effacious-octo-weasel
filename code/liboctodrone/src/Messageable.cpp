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

void Messageable::runCommMod()
{
	communicationsModule->set_messageable(this);
	communicationsModule->comm_function();
}

CommMod* Messageable::get_comm_mod(){
	return communicationsModule;
}
