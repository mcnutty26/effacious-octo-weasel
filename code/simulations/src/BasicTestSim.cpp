#include "BasicTest.hpp"
#include <Environment.hpp>
#include <Basic.hpp>
#include <CommMod.hpp>
#include <map>
#include <atomic>

int main(int argv, char* argc[]){
	//create the sensor map and optionally add in some data
	std::map<std::string, data_type>* sensor_map = new std::map<std::string, data_type>;
	//data_type* sensor_data = new data_type();
	//sensor_map.insert(std::pair<std::string, int>("blank", sensor_data));

	//create the environment and comm module
	Environment* env = new Environment(*sensor_map, 1.0);
	std::atomic_flag stdout_lock = ATOMIC_FLAG_INIT;

	CommMod* comm_basic1 = new Basic(env, &stdout_lock);
	CommMod* comm_basic2 = new Basic(env, &stdout_lock);

	//create and add drones
	BasicTest* drone1 = new BasicTest(comm_basic1, 0.0, 0.0, 0.0, 0.0, env, false);
	BasicTest* drone2 = new BasicTest(comm_basic2, 1.0, 1.0, 0.0, 0.0, env, true);
	env->addDrone(drone1);
	env->addDrone(drone2);

	//run the simulation
	env->run();
}
