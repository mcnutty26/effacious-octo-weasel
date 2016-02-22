#include "AodvComms.hpp"
#include <Environment.hpp>
#include <Aodv.hpp>
#include <CommMod.hpp>
#include <map>
#include <atomic>

int main(int argv, char* argc[]){
	//create the sensor map and optionally add in some data
	std::map<std::string, data_type>* sensor_map = new std::map<std::string, data_type>;
	//data_type* sensor_data = new data_type();
	//sensor_map.insert(std::pair<std::string, int>("blank", sensor_data));

	//create the environment and comm modules
	Environment* env = new Environment(*sensor_map);
	std::atomic_flag stdout_lock = ATOMIC_FLAG_INIT;

	bool debug_mode = true;
	CommMod* comm_aodv1 = new Aodv(env, "10.0.0.1", &stdout_lock, debug_mode);
	CommMod* comm_aodv2 = new Aodv(env, "10.0.0.2", &stdout_lock, debug_mode);
	CommMod* comm_aodv3 = new Aodv(env, "10.0.0.3", &stdout_lock, debug_mode);

	//create and add drones
	AodvComms* drone1 = new AodvComms(comm_aodv1, 0.0, 0.0, 0.0, 0.0, env, 0);
	AodvComms* drone2 = new AodvComms(comm_aodv2, 0.0, 7.0, 0.0, 0.0, env, -1);
	AodvComms* drone3 = new AodvComms(comm_aodv3, 0.0, 14.0, 0.0, 0.0, env, 1);
	env->addMessageable(drone1);
	env->addMessageable(drone2);
	env->addMessageable(drone3);

	//run the simulation
	env->run();
}
