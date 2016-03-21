///Basic message with addressing information

#include "Basic_message_addressed.hpp"

Basic_message_addressed::Basic_message_addressed(std::string msg, std::string dst, std::string src): Basic_message(msg){
    destination = dst;
	source = src;
}

///Returns a string representation of the message
std::string Basic_message_addressed::to_string(){
	return destination + ";" + source + ";" + Basic_message::to_string();
}

///Getter method for the message content
std::string Basic_message_addressed::get_message(){
	return Basic_message::to_string();
}

///Getter method for the IP address of the node this message is destined for
std::string Basic_message_addressed::get_destination(){
	return destination;
}

///Getter method for the IP address of the node which sent this message
std::string Basic_message_addressed::get_source(){
	return source;
}
