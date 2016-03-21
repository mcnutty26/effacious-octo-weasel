///A basic message containing a payload wth no addressing information

#include "Basic_message.hpp"

Basic_message::Basic_message(std::string msg): Message("BASIC"){
    message = msg;
}

///Returns a string representation of the message
std::string Basic_message::to_string(){
	return message;
}
