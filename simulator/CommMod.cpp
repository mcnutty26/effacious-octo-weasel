#include "CommMod.hpp"

CommMod::CommMod(Envrionment* env)
{
	environment = env;
}

void broadcast(std::string message, double xPos, double yPos, double zPos, double range)
{
	environment->broadcast(message, xPos, yPos, zPos, range);
}

void CommMod::push_in_message(std::string message)
{
	inQueue.push(message);
}

void COmmMod::push_out_message(std::string message)
{
	outQueue.push(message);
}
