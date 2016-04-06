/*
This file is part of octoDrone.

octoDrone is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

octoDrone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with octoDrone.  If not, see <http://www.gnu.org/licenses/>.
*/

///Basic message with addressing information

#include "Basic_addressed_message.hpp"

Basic_addressed_message::Basic_addressed_message(std::string msg, std::string dst, std::string src): Basic_message(msg){
    destination = dst;
	source = src;
}

///Returns a string representation of the message
std::string Basic_addressed_message::to_string(){
	return destination + ";" + source + ";" + Basic_message::to_string();
}

///Getter method for the message content
std::string Basic_addressed_message::get_message(){
	return Basic_message::to_string();
}

///Getter method for the IP address of the node this message is destined for
std::string Basic_addressed_message::get_destination(){
	return destination;
}

///Getter method for the IP address of the node which sent this message
std::string Basic_addressed_message::get_source(){
	return source;
}
