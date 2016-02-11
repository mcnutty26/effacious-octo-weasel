#include "AodvComms.hpp"
#include <Environment.hpp>
#include <Aodv.hpp>
#include <CommMod.hpp>
#include <map>

int main(int argv, char* argc[]){
	//create the sensor map and optionally add in some data
	std::map<std::string, data_type>* sensor_map = new std::map<std::string, data_type>;
	//data_type* sensor_data = new data_type();
	//sensor_map.insert(std::pair<std::string, int>("blank", sensor_data));

	//create the environment and comm modules
	Environment* env = new Environment(*sensor_map);
	CommMod* comm_aodv1 = new Aodv(env, "10.0.0.1");
	CommMod* comm_aodv2 = new Aodv(env, "10.0.0.2");

	//create and add drones
	AodvComms* drone1 = new AodvComms(comm_aodv1, 0.0, 0.0, 0.0, 0.0, env, false);
	AodvComms* drone2 = new AodvComms(comm_aodv2, 1.0, 1.0, 0.0, 0.0, env, true);
	env->addMessageable(drone1);
	env->addMessageable(drone2);

	//run the simulation
	env->run();
}
