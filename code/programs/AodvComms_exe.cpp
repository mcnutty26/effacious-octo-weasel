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
	Environment* env = new Environment(*sensor_map, 0.01);
	std::atomic_flag stdout_lock = ATOMIC_FLAG_INIT;

	bool debug_mode = true;
	CommMod* comm_aodv1 = new Aodv(env, "10.0.0.1", &stdout_lock, debug_mode);
	CommMod* comm_aodv2 = new Aodv(env, "10.0.0.2", &stdout_lock, debug_mode);
	CommMod* comm_aodv3 = new Aodv(env, "10.0.0.3", &stdout_lock, debug_mode);
	//CommMod* comm_aodv4 = new Aodv(env, "10.0.0.4", &stdout_lock, debug_mode);

	//create and add drones
	int flag = 0;
	AodvComms* drone1 = new AodvComms(comm_aodv1, 0.0, 0.0, 0.0, 0.0, env, 0, &flag);
	AodvComms* drone2 = new AodvComms(comm_aodv2, 0.0, 7.0, 0.0, 0.0, env, -1, &flag);
	AodvComms* drone3 = new AodvComms(comm_aodv3, 0.0, 14.0, 0.0, 0.0, env, 1, &flag);
	//AodvComms* drone4 = new AodvComms(comm_aodv4, 0.0, 21.0, 0.0, 0.0, env, 1, &flag);
	env->addDrone(drone1);
	env->addDrone(drone2);
	env->addDrone(drone3);
	//env->addDrone(drone4);

	//run the simulation
	env->run();
}
