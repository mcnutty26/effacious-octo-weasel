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

#include "BasicTest.hpp"
#include <iostream>
#include <Basic_message.hpp>

BasicTest::BasicTest(CommMod* cm, double xp, double yp, double zp, double speed, Environment* env, bool sink): Drone(cm, xp, yp, zp, speed, env){
	sink_node = sink;
};

bool BasicTest::message_callback(Message*){
    return false;
}

void BasicTest::run(){
	if (sink_node){
		std::cout << "Sink waiting for message" << std::endl;
		std::cout << wait_for_message()->to_string() << std::endl;
		send_message(new Basic_message("KILL"));
	} else {
		std::cout << "Source sending message" << std::endl;
		send_message(new Basic_message("TEST MESSAGE PLEASE IGNORE"));
		send_message(new Basic_message("KILL"));
	}
}

