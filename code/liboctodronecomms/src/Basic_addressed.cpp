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

///Basic messaging protocol with addressing for testing, where nodes receive all messages sent if they are within range and addressed to them

#include "Basic_addressed.hpp"
#include <Message.hpp>
#include <queue>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include "Basic_addressed_message.hpp"

Basic_addressed::Basic_addressed(Environment* env, std::atomic_flag* flag, std::string ip): CommMod(env){
    RANGE = 1000000.0f;
    lock = flag;
    ip_address = ip;
}

///The main communications loop which handles incomming and outgoing messages
/**
 * Every loop any incomming messages are deserialized and delivered if they match our IP address
 * Next, any outgoing messages are sent
 * Note that received messages not addressed to this IP address will be dropped
 */
void Basic_addressed::comm_function(){
	while(true){
		while (!inQueue.empty()){
			std::string message = inQueue.front();
			inQueue.pop();

			std::string dst_ip = Basic_addressed::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
			std::string src_ip = Basic_addressed::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
			std::string content = Basic_addressed::get_attribute(message);

			if (dst_ip != ip_address && dst_ip != "255.255.255.255"){
				log("dropped message");
				break;
			}

			Message* to_push = new Basic_addressed_message(content, dst_ip, src_ip);
			messageable->push_message(to_push);
			log("rec'd message");
		}

		while (!outQueue.empty()){
			Message* message = outQueue.front();
			outQueue.pop();
			
			std::string message_string = message->to_string();
			std::string dst_ip = Basic_addressed::get_attribute(message_string);
			message_string.erase(message_string.begin(), message_string.begin() + message_string.find_last_of(";") + 1);
			//std::string content = Basic_addressed::get_attribute(message_string);

			Basic_addressed_message* addressed_message = new Basic_addressed_message(message_string, dst_ip, ip_address);
			
			if (message->to_string() == "KILL"){
			    log("exiting");
			    return;
			}
			
			double xpos = messageable->getX();
			double ypos = messageable->getY();;
			double zpos = messageable->getZ();
			//environment->broadcast(message->to_string(), xpos, ypos, zpos, RANGE, this); 
			environment->broadcast(addressed_message->to_string(), xpos, ypos, zpos, RANGE, this); 
			log("broadcast message");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Basic_addressed::log(std::string log_message){
	while (lock->test_and_set()){}
	std::cout << "basic_addressed@" << ip_address << ": " << log_message << std::endl;
	lock->clear();
}

std::string Basic_addressed::get_attribute(std::string message){
	std::string attribute;
	std::stringstream attr;
	attr.str(message);
	std::getline(attr, attribute, ';');
	return attribute;
}
