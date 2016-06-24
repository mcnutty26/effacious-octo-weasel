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

#include "BasicAddrTest.hpp"
#include <Basic_addressed_message.hpp>
#include <iostream>
#include <chrono>
#include <sstream>

BasicAddrTest::BasicAddrTest(CommMod* cm, double xp, double yp, double zp, double speed, Environment* env, std::atomic_flag* flag, bool sink, int count): Drone(cm, xp, yp, zp, speed, env){
	sink_node = sink;
	m_flag = flag;
	m_env = env;
	m_count = count;
};

bool BasicAddrTest::message_callback(Message*){
    return false;
}

void BasicAddrTest::run(){
	if (sink_node){
		int recd = 0;
		while (recd < m_count){
			++recd;
			while (m_flag->test_and_set()){};
			std::cout << "Sink waiting for message" << std::endl;
			m_flag->clear();
		
			wait_for_message();
			while (m_flag->test_and_set()){};
			std::cout << "Sink rec'd " << std::to_string(recd) << std::endl;
			m_flag->clear();
		}
		send_message(new Basic_message("KILL"));
	} else {
		while (m_flag->test_and_set()){};
		std::cout << "Source sending message" << std::endl;
		m_flag->clear();
		send_message(new Basic_addressed_message("TEST MESSAGE PLEASE IGNORE", "10.0.0.1", ""));
		send_message(new Basic_message("KILL"));
	}
}

void BasicAddrTest::log(std::string message){
	while(m_flag->test_and_set()){}
	std::ostringstream time_stream;
	time_stream << m_env->getTime();
	std::string time_string  = time_stream.str();
	std::cout << "(" + time_string + ")scale@basic_addr: " << message << std::endl;
	m_flag->clear();
}

