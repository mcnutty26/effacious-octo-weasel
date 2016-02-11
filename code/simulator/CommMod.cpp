#include "CommMod.hpp"

CommMod::CommMod(Environment* env)
{
	environment = env;
}

void CommMod::broadcast(Message* message, double xPos, double yPos, double zPos, double range)
{
	environment->broadcast(message->to_string(), xPos, yPos, zPos, range);
}

void CommMod::broadcast(std::string message, double xPos, double yPos, double zPos, double range)
{
	environment->broadcast(message, xPos, yPos, zPos, range);
}

void CommMod::push_in_message(std::string message)
{
	inQueue.push(message);
}

void CommMod::push_out_message(Message* message)
{
	outQueue.push(message);
}

void CommMod::set_messageable(Messageable* msg)
{
	messageable = msg;
}
