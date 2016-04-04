#include "BasicAddrTest.hpp"
#include <iostream>
#include <Basic_message.hpp>

BasicAddrTest::BasicAddrTest(CommMod* cm, double xp, double yp, double zp, double speed, Environment* env, bool sink): Drone(cm, xp, yp, zp, speed, env){
	sink_node = sink;
};

bool BasicAddrTest::message_callback(Message*){
    return false;
}

void BasicAddrTest::run(){
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
