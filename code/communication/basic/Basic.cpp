#include "Basic.hpp"
#include <Message.hpp>
#include <queue>

Basic::Basic(Environment* env): CommMod(env){
    RANGE = 1000000.0f;
    environment = env;
}

void Basic::comm_function(){
	while (!inQueue.empty()){
		
	}
	while (!outQueue.empty()){
		Message* message = outQueue.front();
		outQueue.pop();
		double xpos = 0.0f;
		double ypos = 0.0f;
		double zpos = 0.0f;
		environment->broadcast(message->to_string(), xpos, ypos, zpos, RANGE); 
	}
}
