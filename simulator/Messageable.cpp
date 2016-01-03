#include "Messageable.hpp"

Messageable::Messageable(CommMod* cm)
{
	messageFun = nullptr;
	communicationsModule = cm;
}

void Messageable::send_message(std::string contents)
{
	communicationsModule->push_out_message(contents);
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
