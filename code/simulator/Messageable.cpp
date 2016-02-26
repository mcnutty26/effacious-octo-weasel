#include "Messageable.hpp"

Messageable::Messageable(CommMod* cm, double xp, double yp, double zp)
{
	communicationsModule = cm;

	xPos = xp;
	yPos = yp;
	zPos = zp;
}

double Messageable::getX()
{
	return xPos;
}

double Messageable::getY()
{
	return yPos;
}

double Messageable::getZ()
{
	return zPos;
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
