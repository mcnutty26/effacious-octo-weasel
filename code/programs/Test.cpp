#include "Test.hpp"
#include <iostream>
#include <Basic.hpp>
#include <Basic_message.hpp>
#include <BaseStation.hpp>

Test::Test(CommMod* cm, double xp, double yp, double zp, double speed, Environment* env, bool sink): Drone(cm, xp, yp, zp, speed, env){
	sink_node = sink;
};

bool Test::message_callback(Message*){
    return false;
}

void Test::run(){
	if (sink_node){
		std::cout << "Sink waiting for message" << std::endl;
		std::cout << wait_for_message()->to_string() << std::endl;
	} else {
		std::cout << "Source sending message" << std::endl;
		send_message(new Basic_message("TEST MESSAGE PLEASE IGNORE"));
	}
}

int main(int argv, char* argc[]){
	//create the sensor map and optionally add in some data
	std::map<std::string, data_type>* sensor_map = new std::map<std::string, data_type>;
	//data_type* sensor_data = new data_type();
	//sensor_map.insert(std::pair<std::string, int>("blank", sensor_data));

	//create the environment and comm module
	Environment* env = new Environment(*sensor_map);
	CommMod* comm_basic = new Basic(env);

	//create and add a basestation
	//BaseStation* base = new BaseStation(comm_basic, 0.0, 0.0, 0.0);

	//create and add drones
	Test* drone1 = new Test(comm_basic, 0.0, 0.0, 0.0, 0.0, env, false);
	Test* drone2 = new Test(comm_basic, 1.0, 1.0, 0.0, 0.0, env, true);
	env->addMessageable(drone1);
	env->addMessageable(drone2);
	env->run();
}
