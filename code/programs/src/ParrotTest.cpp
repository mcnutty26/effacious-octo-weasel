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

#include "ParrotTest.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <Basic_message.hpp>

ParrotTest::ParrotTest(CommMod* cm, double xp, double yp, double zp, double speed, Environment* env, bool sink_node): Drone(cm, xp, yp, zp, speed, env){
	m_sink_node = sink_node;
};

bool ParrotTest::message_callback(Message*){
    return false;
}

void ParrotTest::run(){
	if (m_sink_node){
		std::cout << "ParrotTest: sink waiting for message" << std::endl;
		if (wait_for_message()->to_string() == "TEST"){
			std::cout << "ParrotTest: received message" << std::endl;
			move(Direction::FORWARD, 0.5, 1);
			while(!hasFinishedMoving()){}
			turn(180);
			while(!hasFinishedMoving()){}
		}
	} else {
		std::cout << "ParrotTest: source sending message" << std::endl;
		send_message(new Basic_message("TEST"));
	}
	send_message(new Basic_message("KILL"));
	std::cout << "ParrotTest: exiting" << std::endl;
	kill();
}

