#include "Messageable.hpp"

Messageable::Messageable(CommMod* cm, double xp, double yp, double zp)
{
	messageFun = nullptr;
	communicationsModule = cm;

	xPos = xp;
	yPos = yp;
	zPos = zp;
}

double getX()
{
	return xPos;
}

double getY()
{
	return yPos;
}

double getZ()
{
	return zPos;
}

void Messageable::send_message(std::string contents)
{
	communicationsModule->push_out_message(contents);
}

void Messageable::receive_message(std::string contents)
{
	communicationsModule->push_in_message(contents);
}

std::string Messageable::wait_for_message()
{
	while(inQueue.empty()){}
	std::string message = inQueue.front();
	inQueue.pop();
	return message;
}

void Messageable::push_message(std::string contents)
{
	if(!message_callback(contents))
	{
		inQueue.push(contents);
	}
}
