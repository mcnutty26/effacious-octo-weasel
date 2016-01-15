#include "Messageable.hpp"

Messageable::Messageable(CommMod* cm, double xp, double yp, double zp, std::string ip_addr)
{
	messageFun = nullptr;
	communicationsModule = cm;

	xPos = xp;
	yPos = yp;
	zPos = zp;
  
  ip_address = ip_addr
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

void Messageable::send_message(Message contents)
{
	communicationsModule->push_out_message(contents);
}

void Messageable::receive_message(Message contents)
{
	communicationsModule->push_in_message(contents);
}

Message Messageable::wait_for_message()
{
	while(inQueue.empty()){}
	std::string message = inQueue.front();
	inQueue.pop();
	return message;
}

void Messageable::push_message(Message contents)
{
	if(!message_callback(contents))
	{
		inQueue.push(contents);
	}
}
