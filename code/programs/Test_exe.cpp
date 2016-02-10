#include "Test.hpp"
#include <Environment.hpp>
#include <Basic.hpp>
#include <CommMod.hpp>
#include <map>

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
