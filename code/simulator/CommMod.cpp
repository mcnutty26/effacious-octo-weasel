#include "CommMod.hpp"

CommMod::CommMod(Envrionment* env, std::string ip_addr)
{
	environment = env;
	ip_address = ip_addr;
}

void broadcast(Message message, double xPos, double yPos, double zPos, double range)
{
	environment->broadcast(message, xPos, yPos, zPos, range);
}

void CommMod::push_in_message(Message message)
{
	inQueue.push(message);
}

void CommMod::push_out_message(Message message)
{
	outQueue.push(message);
}
