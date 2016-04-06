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

#include "ParrotTest.hpp"
#include <Environment.hpp>
#include <Basic.hpp>
#include <CommMod.hpp>
#include <map>
#include <atomic>

int main(int argv, char* argc[]){
	//create the sensor map and optionally add in some data
	std::map<std::string, data_type>* sensor_map = new std::map<std::string, data_type>;

	//create the environment and comm module
	Environment* env = new Environment(*sensor_map, 1.0);
	std::atomic_flag stdout_lock = ATOMIC_FLAG_INIT;

	CommMod* comm_basic = new Basic(env, &stdout_lock);

	//create and add drones
	ParrotTest* drone = new ParrotTest(comm_basic, 0.0, 0.0, 0.0, 0.0, env);
	env->addDrone(drone);

	//run the simulation
	env->run();
}
