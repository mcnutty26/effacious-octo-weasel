#include "Basic.hpp"
#include <Message.hpp>
#include <queue>
#include "Basic_message.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Basic::Basic(Environment* env, std::atomic_flag* flag): CommMod(env){
    RANGE = 1000000.0f;
    environment = env;
    lock = flag;
}

void Basic::comm_function(){
	while(true){
		while (!inQueue.empty()){
			std::string message = inQueue.front();

			if (message == "KILL"){
			    return;
			}

			inQueue.pop();
			Message* to_push = new Basic_message(message);
			messageable->push_message(to_push);
			log("rec'd message");
		}
	
		while (!outQueue.empty()){
			Message* message = outQueue.front();
			outQueue.pop();
			double xpos = messageable->getX();
			double ypos = messageable->getY();;
			double zpos = messageable->getZ();
			environment->broadcast(message->to_string(), xpos, ypos, zpos, RANGE); 
			log("broadcast message");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Basic::log(std::string log_message){
	while (lock->test_and_set()){}
	std::cout << "basic: " << log_message << std::endl;
	lock->clear();
}
