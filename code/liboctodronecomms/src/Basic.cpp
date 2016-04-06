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

///Basic messaging protocol for testing where nodes receive all messages sent if they are within range

#include "Basic.hpp"
#include <Message.hpp>
#include <queue>
#include "Basic_message.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Basic::Basic(Environment* env, std::atomic_flag* flag): CommMod(env){
    RANGE = 1000000.0f;
    lock = flag;
}

///The main communications loop which handles incomming and outgoing messages
/**
 * Every loop we send any messages that are waiting to be sent
 * Then we deliver any messages that we have received
 */
void Basic::comm_function(){
	while(true){
		while (!inQueue.empty()){
			std::string message = inQueue.front();
			inQueue.pop();
			Message* to_push = new Basic_message(message);
			messageable->push_message(to_push);
			log("rec'd message");
		}
	
		while (!outQueue.empty()){
			Message* message = outQueue.front();
			outQueue.pop();
			
			if (message->to_string() == "KILL"){
			    log("exiting");
			    return;
			}
			
			double xpos = messageable->getX();
			double ypos = messageable->getY();;
			double zpos = messageable->getZ();
			environment->broadcast(message->to_string(), xpos, ypos, zpos, RANGE, this); 
			log("broadcast message");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

///Helper function to log internal information
/**
 * Makes use of the stdout lock we were passed on creation to make sure that only one thread is printing at any one time
 */
void Basic::log(std::string log_message){
	while (lock->test_and_set()){}
	std::cout << "basic: " << log_message << std::endl;
	lock->clear();
}
