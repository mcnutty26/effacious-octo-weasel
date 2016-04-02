///Base class for communication algorithm implementations

#include "CommMod.hpp"

CommMod::CommMod(Environment* env)
{
	environment = env;
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
