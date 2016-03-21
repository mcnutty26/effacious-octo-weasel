#include "AodvComms.hpp"
#include <Environment.hpp>
#include <Aodv.hpp>
#include <CommMod.hpp>
#include <IpAllocator.hpp>
#include <map>
#include <atomic>

int main(int argv, char* argc[]){
	//create the sensor map and optionally add in some data
	std::map<std::string, data_type>* sensor_map = new std::map<std::string, data_type>;
	//data_type* sensor_data = new data_type();
	//sensor_map.insert(std::pair<std::string, int>("blank", sensor_data));

	//create the environment and comm modules
	Environment* env = new Environment(*sensor_map, 0.001);
	std::atomic_flag stdout_lock = ATOMIC_FLAG_INIT;

	//Create IP address helper
	IpAllocator allocator = IpAllocator(10, 0, 0, 1);

	bool debug_mode = true;
	CommMod* comm_aodv1 = new Aodv(env, allocator.next(), &stdout_lock, debug_mode);
	CommMod* comm_aodv2 = new Aodv(env, allocator.next(), &stdout_lock, debug_mode);
	CommMod* comm_aodv3 = new Aodv(env, allocator.next(), &stdout_lock, debug_mode);
	CommMod* comm_aodv4 = new Aodv(env, allocator.next(), &stdout_lock, debug_mode);
	CommMod* comm_aodv5 = new Aodv(env, allocator.next(), &stdout_lock, debug_mode);

	//create and add drones
	int flag = 0;
	AodvComms* drone1 = new AodvComms(comm_aodv1, 0.0, 0.0, 0.0, 0.0, env, 0, &flag, &stdout_lock);
	AodvComms* drone2 = new AodvComms(comm_aodv2, 0.0, 7.0, 0.0, 0.0, env, -1, &flag, &stdout_lock);
	AodvComms* drone3 = new AodvComms(comm_aodv3, 0.0, 14.0, 0.0, 0.0, env, -1, &flag, &stdout_lock);
	AodvComms* drone4 = new AodvComms(comm_aodv4, 0.0, 21.0, 0.0, 0.0, env, -1, &flag, &stdout_lock);
	AodvComms* drone5 = new AodvComms(comm_aodv5, 0.0, 28.0, 0.0, 0.0, env, 1, &flag, &stdout_lock);
	env->addDrone(drone1);
	env->addDrone(drone2);
	env->addDrone(drone3);
	env->addDrone(drone4);
	env->addDrone(drone5);

	//run the simulation
	env->run();
}
