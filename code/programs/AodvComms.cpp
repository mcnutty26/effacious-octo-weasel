#include "AodvComms.hpp"
#include <iostream>
#include <Basic_message.hpp>
#include <Basic_message_addressed.hpp>
#include <chrono>
#include <thread>

AodvComms::AodvComms(CommMod* cm, double xp, double yp, double zp, double speed, Environment* env, int function): Drone(cm, xp, yp, zp, speed, env){
	task = function;
};

bool AodvComms::message_callback(Message*){
    return false;
}

void AodvComms::run(){
	if (task == 0){
		std::cout << "Sink waiting for message" << std::endl;
		std::cout << wait_for_message()->to_string() << std::endl;
	} else if (task == 1){
		std::cout << "Source sending message" << std::endl;
		send_message(new Basic_message_addressed("TEST MESSAGE PLEASE IGNORE", "10.0.0.1"));
	} else if (task == -1){
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
	send_message(new Basic_message("KILL"));
}

void AodvComms::talk(std::string message, std::string ip){
	Basic_message* to_send = new Basic_message(ip + ";" + message);
	send_message(to_send);
}
