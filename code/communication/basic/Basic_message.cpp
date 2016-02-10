#include "Basic_message.hpp"

Basic_message::Basic_message(std::string msg): Message("BASIC"){
    message = msg;
}

std::string Basic_message::to_string(){
	return message;
}
