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

#include "AodvTest.hpp"
#include "Dummy_program.hpp"
#include <Environment.hpp>
#include <Aodv.hpp>
#include <Dummy_comm.hpp>
#include <CommMod.hpp>
#include <IpAllocator.hpp>
#include <map>
#include <atomic>

int main(int argv, char* argc[]){
	(void)argv;
	(void)argc;

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
	CommMod* dummy = new Dummy_comm(env);

	//create and add drones
	int flag = 0;
	AodvTest* drone1 = new AodvTest(comm_aodv1, 0.0, 0.0, 0.0, 0.0, env, 0, &flag, &stdout_lock);
	AodvTest* drone2 = new AodvTest(comm_aodv2, 0.0, 7.0, 0.0, 0.0, env, -1, &flag, &stdout_lock);
	AodvTest* drone3 = new AodvTest(comm_aodv3, 0.0, 14.0, 0.0, 0.0, env, -1, &flag, &stdout_lock);
	AodvTest* drone4 = new AodvTest(comm_aodv4, 0.0, 21.0, 0.0, 0.0, env, -1, &flag, &stdout_lock);
	AodvTest* drone5 = new AodvTest(comm_aodv5, 0.0, 28.0, 0.0, 0.0, env, 1, &flag, &stdout_lock);
	Dummy_program* base = new Dummy_program(dummy, 0.0, 0.0, 0.0);
	env->addDrone(drone1);
	env->addDrone(drone2);
	env->addDrone(drone3);
	env->addDrone(drone4);
	env->addDrone(drone5);
	env->setBaseStation(base);

	//run the simulation
	env->run();
}
