#include "Basic_message_addressed.hpp"

Basic_message_addressed::Basic_message_addressed(std::string msg, std::string dst): Basic_message(msg){
    destination = dst;
}

std::string Basic_message_addressed::to_string(){
	return destination + ";" + Basic_message::to_string();
}

std::string Basic_message_addressed::get_message(){
	return Basic_message::to_string();
}

std::string Basic_message_addressed::get_destination(){
	return destination;
}
