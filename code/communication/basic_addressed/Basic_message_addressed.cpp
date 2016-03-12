#include "Basic_message_addressed.hpp"

Basic_message_addressed::Basic_message_addressed(std::string msg, std::string dst, std::string src): Basic_message(msg){
    destination = dst;
	source = src;
}

std::string Basic_message_addressed::to_string(){
	return destination + ";" + source + ";" + Basic_message::to_string();
}

std::string Basic_message_addressed::get_message(){
	return Basic_message::to_string();
}

std::string Basic_message_addressed::get_destination(){
	return destination;
}

std::string Basic_message_addressed::get_source(){
	return source;
}
