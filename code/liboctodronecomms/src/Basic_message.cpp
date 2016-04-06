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

///A basic message containing a payload wth no addressing information

#include "Basic_message.hpp"

Basic_message::Basic_message(std::string msg): Message("BASIC"){
    message = msg;
}

///Returns a string representation of the message
std::string Basic_message::to_string(){
	return message;
}
