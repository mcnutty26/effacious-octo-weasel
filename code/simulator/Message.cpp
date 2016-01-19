#include "Message.hpp"

Message::Message(std::string type)
{
	this->type = type;
}

Message::Message(std::string type, std::string initialiser)
:Message(type)
{
	from_string(initialiser)
}

time_t Message::get_current_time()
{
	return time(nullptr);
}

std::string Message::get_type()
{
	return type;
}
