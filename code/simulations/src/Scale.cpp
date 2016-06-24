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

#include "BasicAddrTest.hpp"
#include "Dummy_program.hpp"
#include <Environment.hpp>
#include <IpAllocator.hpp>
#include <Basic_addressed.hpp>
#include <CommMod.hpp>
#include <Dummy_comm.hpp>
#include <map>
#include <atomic>

int main(int argc, char* argv[]){

	int count = 1;
	if (argc == 2){
		count = atoi(argv[1]);
	}

	//create the sensor map and optionally add in some data
	std::map<std::string, data_type>* sensor_map = new std::map<std::string, data_type>;

	//create the environment and comm module
	Environment* env = new Environment(*sensor_map, 0.01, false);
	std::atomic_flag stdout_lock = ATOMIC_FLAG_INIT;
	
	//Create an IP address allocator
	IpAllocator allocator = IpAllocator(10,0,0,1);

	//Create the sink and dummy base station
	CommMod* comm_sink = new Basic_addressed(env, &stdout_lock, allocator.next());
	BasicAddrTest* sink = new BasicAddrTest(comm_sink, 0.0, 0.0, 0.0, 0.0, env, &stdout_lock, true, count);
	env->addDrone(sink);
	CommMod* comm_dummy = new Dummy_comm(env);
	Dummy_program* base = new Dummy_program(comm_dummy, 0.0, 0.0, 0.0);
	env->setBaseStation(base);

	//Create some source nodes
	for (int i = 1; i <= count; i++){
		CommMod* comm_source = new Basic_addressed(env, &stdout_lock, allocator.next());
		BasicAddrTest* source = new BasicAddrTest(comm_source, 1.0, 1.0, 0.0, 0.0, env, &stdout_lock, false, count);
		env->addDrone(source);
	}

	//run the simulation
	env->run();
}
