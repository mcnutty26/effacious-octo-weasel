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

///Modified implementation of Environment for the Parrot AR 2 drone

#include "Environment.hpp"
#include "Drone.hpp"
#include "BaseStation.hpp"

#include <cmath>
#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#define MULTICAST_ADDR "239.0.0.1"
#define MULTICAST_PORT 8080

std::atomic_flag lock_broadcast = ATOMIC_FLAG_INIT;
bool run_comms = true;
bool drop_packet = false;
std::thread commServ;

std::string passStr(std::string in)
{
	return in;
}

///Starts the node server which connects to the drone
void startNode(){
	//start the node server
	if (system("node ../liboctodroneparrot/src/js/parrot.js &") < 0){
		std::cout << "error@nodeServer: starting process" << std::endl;
		exit(1);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

///Returns the only drone in the sharded environment
Drone* Environment::getDrone(){
	return drones[0];
}

///Listens for communications from other drones
void commServer(bool* flag, bool* drop_packet, Environment* env, std::string if_addr){

	//set up variables
	struct ip_mreq mreq;
	struct sockaddr_in addr;
	int sock;
	char message_buffer[256];
	socklen_t addrlen;

	//get a file descriptor for a socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		std::cout << "error@commServer: opening socket (" << strerror(errno) << ")" << std::endl;
		exit(1);
	}

	//set binding options
	bzero((char *)&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(MULTICAST_PORT);
	addrlen = (socklen_t)sizeof(addr);

	//bind the socket to a port
	if (bind(sock, (struct sockaddr *) &addr, addrlen) < 0) {        
		std::cout << "error@commServer: binding (" << strerror(errno) << ")" << std::endl;
		exit(1);
	}

	//configure multicast and select a network interface
	mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_ADDR);
	inet_pton(AF_INET, if_addr.c_str(), &mreq.imr_interface.s_addr);
	if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
		std::cout << "error@commServer: configuring multicast (" << strerror(errno) << ")" << std::endl;
		exit(1);
	}

	//start receive loop
	std::cout << "init@commServer: listening on " << if_addr << std::endl;
	while (1) {
		//block until we receive a message on the multicast address
		if (recvfrom(sock, message_buffer, sizeof(message_buffer), 0, (struct sockaddr *) &addr, &addrlen) < 0){
			std::cout << "error@commServer: reading from socket (" << strerror(errno) << ")" << std::endl;
			exit(1);
		}

		//deliver the message to the drone if it was not sent by the drone
		std::string message  = message_buffer;
		if (message != "KILL"){
		 	printf("message@commServer: %s from %s\n", message_buffer, inet_ntoa(addr.sin_addr));
		}
		if (*drop_packet == false){
			env->getDrone()->receive_message(message);
		} else if (message != "KILL"){
			std::cout << "message@commServer: dropped" << std::endl;
			*drop_packet = false;
		}
		bzero(message_buffer, 256);

		//check to see if the program is still running
		if (*flag == false){
			std::cout << "exit@commServer: shutting down" << std::endl;
			break;
		}
	}
}

Environment::Environment(std::map<std::string, data_type> sensor_data, std::function <std::string(std::string)> nfun, std::string address)
:noiseFun(nfun)
{
	data = sensor_data;
	baseStation = NULL;
	startNode();
	commServ = std::thread(commServer, &run_comms, &drop_packet, this, if_addr);
	if_addr = address;
};

Environment::Environment(std::map<std::string, data_type> sensor_data, std::string address)
{
	data = sensor_data;
	noiseFun = &passStr;
	baseStation = NULL;
	startNode();
	if_addr = address;
	commServ = std::thread(commServer, &run_comms, &drop_packet, this, if_addr);
}

//should not be called by anything other than the main thread
void Environment::addData(std::string type, data_type d)
{
	data[type] = d;
}

//should not be called by anything other than the main thread
void Environment::addDrone(Drone* m)
{
	drones.push_back(m);
}

void Environment::setBaseStation(BaseStation* b){
    baseStation = b;
}

void Environment::broadcast(std::string message, double xOrigin, double yOrigin, double zOrigin, double range, CommMod* caller)
{
	(void)xOrigin;
	(void)yOrigin;
	(void)zOrigin;
	(void)range;
	(void)caller;

	std::string nMessage = noiseFun(message);
	while(lock_broadcast.test_and_set()){}

	//set up variables
	struct sockaddr_in addr;
	struct in_addr interface_addr;
	socklen_t addrlen;
	int sock;
   
	//get a file descriptor for a socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0){
		std::cout << "error@commServer: opening socket (" << strerror(errno) << ")" << std::endl;
		exit(1);
	}

	//set multicast address and port to send to
	bzero((char *)&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(MULTICAST_ADDR);
	addr.sin_port = htons(MULTICAST_PORT);
	addrlen = (socklen_t)sizeof(addr);

	//configure multicast and choose a network interface
	inet_pton(AF_INET, if_addr.c_str(), &interface_addr);
	if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, &interface_addr, sizeof(interface_addr)) < 0){
		std::cout << "error@commServer: set interface address" << strerror(errno) << std::endl;
		exit(1);
	}

	//send the message, and set a flag so that the packet gets dropped when this unit receives it
	if (message != "KILL"){
		std::cout << "message@commServer: sending " << message << " from interface with address " << if_addr << std::endl;
	}
	drop_packet = true;
	 if (sendto(sock, message.c_str(), strlen(message.c_str()), 0, (struct sockaddr *) &addr, addrlen) < 0){
		std::cout << "error@commServer: sending (" << strerror(errno) << ")" << std::endl;
		exit(1);
	}

	lock_broadcast.clear();
}

bool allRunning(std::vector<Drone*>* drones)
{
	bool running = false;
	for(auto x = drones->begin(); x != drones->end(); ++x)
	{
		running |= (*x)->getAlive();
	}
	return running;
}

void Environment::run()
{
	if (baseStation == nullptr){
		std::cout << "error@environment: no base station" << std::endl;
		exit(1);
	}

	std::vector<std::thread> threads;
	for(auto x: drones)
	{
		threads.emplace_back(&Drone::run_wrapper, x);
		threads.emplace_back(&Drone::runCommMod, x);
	}

	if (baseStation != NULL)
	{
		threads.emplace_back(&BaseStation::run_wrapper, baseStation);
		threads.emplace_back(&BaseStation::runCommMod, baseStation);
	}

	while(allRunning(&drones) || baseStation->getAlive())
	{
		for(auto x: drones)
		{
			if(x->isAlive())
			{
				x->upkeep(false);
			}
		}
	}

	for(std::vector<std::thread>::size_type i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}

	//shut down the comms server
	run_comms = 0;
	broadcast("KILL", 0.0, 0.0, 0.0, 0.0, NULL);
	commServ.join();
}

///Modified to use real time
double Environment::getTime()
{
	return time(nullptr);
}

double Environment::getData(std::string type, double x, double y, double z)
{
	return data[type][(int)std::round(x)][(int)std::round(y)][(int)std::round(z)];
}
