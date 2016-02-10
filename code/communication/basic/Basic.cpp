#include "Basic.hpp"
#include <Message.hpp>
#include <queue>
#include "Basic_message.hpp"
#include <iostream>

Basic::Basic(Environment* env): CommMod(env){
    RANGE = 1000000.0f;
    environment = env;
}

void Basic::comm_function(){
	while (!inQueue.empty()){
		std::string message = inQueue.front();
		inQueue.pop();
		Message* to_push = new Basic_message(message);
		messageable->push_message(to_push);
		std::cout << "Basic: rec'd message" << std::endl;
	}
	
	while (!outQueue.empty()){
		Message* message = outQueue.front();
		outQueue.pop();
		double xpos = messageable->getX();
		double ypos = messageable->getY();;
		double zpos = messageable->getZ();
		environment->broadcast(message->to_string(), xpos, ypos, zpos, RANGE); 
		std::cout << "Basic: broadcast message" << std::endl;
	}
}
