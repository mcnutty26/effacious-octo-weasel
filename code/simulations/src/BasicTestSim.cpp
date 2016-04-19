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

#include "BasicTest.hpp"
#include "Dummy_program.hpp"
#include <Environment.hpp>
#include <Basic.hpp>
#include <CommMod.hpp>
#include <Dummy_comm.hpp>
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

	CommMod* comm_basic1 = new Basic(env, &stdout_lock);
	CommMod* comm_basic2 = new Basic(env, &stdout_lock);
	CommMod* comm_dummy = new Dummy_comm(env);

	//create and add drones
	BasicTest* drone1 = new BasicTest(comm_basic1, 0.0, 0.0, 0.0, 0.0, env, false);
	BasicTest* drone2 = new BasicTest(comm_basic2, 1.0, 1.0, 0.0, 0.0, env, true);
	Dummy_program* base = new Dummy_program(comm_dummy, 0.0, 0.0, 0.0);
	env->addDrone(drone1);
	env->addDrone(drone2);
	env->setBaseStation(base);

	//run the simulation
	env->run();
}
