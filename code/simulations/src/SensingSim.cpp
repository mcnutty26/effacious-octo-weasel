/*
This file is part of octoDrone.

octoDrone is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

octoDrone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with octoDrone.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SensingDrone.hpp"
#include "SensingBaseStation.hpp"
#include <Environment.hpp>
#include <Basic_addressed.hpp>
#include <CommMod.hpp>
//#include <IpAllocator.hpp>
#include <map>
#include <atomic>

int main(int argv, char* argc[]){
	(void)argv;
	(void)argc;

	//create the sensor map and optionally add in some data
	std::map<std::string, data_type>* sensor_map = new std::map<std::string, data_type>;
	//data_type* sensor_data = new data_type();
	//sensor_map.insert(std::pair<std::string, int>("blank", sensor_data));

	//create the environment and comm module
	Environment* env = new Environment(*sensor_map, 1.0);
	std::atomic_flag stdout_lock = ATOMIC_FLAG_INIT;

	// Create IP address helper
	//IpAllocator allocator = IpAllocator(10, 0, 0, 1);


	CommMod* comm_basic1 = new Basic_addressed(env, &stdout_lock, "10.0.0.1");
	CommMod* comm_basic2 = new Basic_addressed(env, &stdout_lock, "10.0.0.2");

	CommMod* comm_basic_base = new Basic_addressed(env, &stdout_lock, "10.0.0.255");

	//creat and add base station
	SensingBaseStation* basestation = new SensingBaseStation(comm_basic_base, 0.0, 0.0, 0.0, 1.0, 1.0, 10.0, 10.0);
	env->setBaseStation(basestation);

	//create and add drones
	SensingDrone* drone1 = new SensingDrone(comm_basic1, 1.0, 1.0, 0.0, 0.0, 0.5, env, false);
	SensingDrone* drone2 = new SensingDrone(comm_basic2, 2.0, 2.0, 0.0, 0.0, 0.5, env, true);
	env->addDrone(drone1);
	env->addDrone(drone2);

	//run the simulation
	env->run();
}
