#include "Message.hpp"

Message::Message(std::string type)
{
	this->type = type;
}

time_t Message::get_current_time()
{
	return time(nullptr);
}

std::string Message::get_type()
{
	return type;
}
