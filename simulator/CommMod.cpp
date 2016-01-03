#include "CommMod.hpp"

void CommMod::push_in_message(std::string message)
{
	inQueue.push(message);
}

void COmmMod::push_out_message(std::string message)
{
	outQueue.push(message);
}
