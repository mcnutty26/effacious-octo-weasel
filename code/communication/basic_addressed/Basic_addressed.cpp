#include "Basic_addressed.hpp"
#include <Message.hpp>
#include <queue>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include "Basic_message_addressed.hpp"

Basic_addressed::Basic_addressed(Environment* env, std::atomic_flag* flag, std::string ip): CommMod(env){
    RANGE = 1000000.0f;
    environment = env;
    lock = flag;
    ip_address = ip;
}

void Basic_addressed::comm_function(){
	while(true){
		while (!inQueue.empty()){
			std::string message = inQueue.front();
			inQueue.pop();

			std::string dst_ip = Basic_addressed::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
			std::string content = Basic_addressed::get_attribute(message);

			if (dst_ip != ip_address){
				log("dropped message");
				break;
			}

			Message* to_push = new Basic_message_addressed(content, dst_ip);
			messageable->push_message(to_push);
			log("rec'd message");
		}
	
		while (!outQueue.empty()){
			Message* message = outQueue.front();
			outQueue.pop();
			
			std::string message_string = message->to_string();
			std::string dst_ip = Basic_addressed::get_attribute(message_string);
			message_string.erase(message_string.begin(), message_string.begin() + message_string.find_first_of(";") + 1);
			std::string content = Basic_addressed::get_attribute(message_string);

			Basic_message_addressed* addressed_message = new Basic_message_addressed(content, dst_ip);
			
			if (content == "KILL"){
			    log("exiting");
			    return;
			}
			
			double xpos = messageable->getX();
			double ypos = messageable->getY();;
			double zpos = messageable->getZ();
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
