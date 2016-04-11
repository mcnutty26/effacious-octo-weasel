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

std::atomic_flag lock_broadcast = ATOMIC_FLAG_INIT;
int run_comms = 1;
int drop_packet = 0;
FILE* node_server;
std::thread commServ;

std::string passStr(std::string in)
{
	return in;
}

///Starts the node server which connects to the drone
void startNode(){
	//start the node server
	node_server = popen("node ../liboctodroneparrot/src/js/parrot.js", "w");
	if (!node_server){
		std::cout << "error@nodeServer: starting process" << std::endl;
		exit(1);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

Drone* Environment::getDrone(){
	return drones[0];
}

///Listens for communications from other drones
void commServer(int* flag, int* drop_packet, Environment* env, std::string if_addr){

	struct ip_mreq mreq;
	struct sockaddr_in addr;
	int sock, cnt;
	char msg[256];
	socklen_t addrlen;

   sock = socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) {
     perror("socket");
     exit(1);
   }
   bzero((char *)&addr, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   addr.sin_port = htons(8080);
   addrlen = (socklen_t)sizeof(addr);

 	if (bind(sock, (struct sockaddr *) &addr, addrlen) < 0) {        
         perror("bind");
	 exit(1);
      }    
      mreq.imr_multiaddr.s_addr = inet_addr("239.0.0.1");         
	printf("SENDING ON2 %s\n", if_addr.c_str());
	  inet_pton(AF_INET, if_addr.c_str(), &mreq.imr_interface.s_addr);
      if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
		     &mreq, sizeof(mreq)) < 0) {
	 perror("setsockopt mreq");
	 exit(1);
      }

      while (1) {
 	 cnt = recvfrom(sock, msg, sizeof(msg), 0, 
			(struct sockaddr *) &addr, &addrlen);
	 if (cnt < 0) {
	    perror("recvfrom");
	    exit(1);
	 } else if (cnt == 0) {
 	    break;
	 }
	 printf("%s: message = \"%s\"\n", inet_ntoa(addr.sin_addr), msg);
        }

	//std::cout << "send@commServer: " << message << std::endl;
}

Environment::Environment(std::map<std::string, data_type> sensor_data, std::function <std::string(std::string)> nfun, double timestep, std::string address)
:noiseFun(nfun)
{
	timeStep = timestep;
	data = sensor_data;
	baseStation = NULL;
	startNode();
	commServ = std::thread(commServer, &run_comms, &drop_packet, this, address);
	if_addr = address;
};

Environment::Environment(std::map<std::string, data_type> sensor_data, double timestep, std::string address)
{
	timeStep = timestep;
	data = sensor_data;
	noiseFun = &passStr;
	baseStation = NULL;
	startNode();
	commServ = std::thread(commServer, &run_comms, &drop_packet, this, address);
	if_addr = address;
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
	std::string nMessage = noiseFun(message);
	while(lock_broadcast.test_and_set()){}

	struct sockaddr_in addr;
	socklen_t addrlen;
	int cnt, sock;
   
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0){
		std::cout << "error@commServer: opening socket (" << strerror(errno) << ")" << std::endl;
	exit(1);
   }
   bzero((char *)&addr, sizeof(addr));
      addr.sin_family = AF_INET;
	     addr.sin_addr.s_addr = inet_addr("239.0.0.1");
		    addr.sin_port = htons(8080);

	addrlen = (socklen_t)sizeof(addr);
//      addr.sin_addr.s_addr = inet_addr(EXAMPLE_GROUP);

	struct in_addr interface_addr;
	printf("SENDING ON %s\n", if_addr.c_str());
	inet_pton(AF_INET, if_addr.c_str(), &interface_addr);
	if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, &interface_addr, sizeof(interface_addr)) < 0){
		std::cout << "set if " << strerror(errno) << std::endl;
		exit(1);
	}

	 printf("sending: %s\n", message.c_str());
	 cnt = sendto(sock, message.c_str(), strlen(message.c_str()), 0, (struct sockaddr *) &addr, addrlen);
	 if (cnt < 0) {
		 std::cout << "sendto " << strerror(errno) << std::endl;
	    exit(1);
	 }

	lock_broadcast.clear();
}

bool allRunning(std::vector<std::thread>* threads)
{
	bool running = false;
	for(auto x = threads->begin(); x != threads->end(); ++x)
	{
		running |= x->joinable();
	}
	return running;
}

void Environment::run()
{
	std::vector<std::thread> threads;
	for(auto x: drones)
	{
		threads.emplace_back(&Drone::run, x);
		threads.emplace_back(&Drone::runCommMod, x);
	}

	if (baseStation != NULL)
	{
		threads.emplace_back(&BaseStation::run, baseStation);
		threads.emplace_back(&BaseStation::runCommMod, baseStation);
	}

	while(allRunning(&threads))
	{
		for(auto x: drones)
		{
			if(x->isAlive())
			{
				x->upkeep();
			}
		}
	}

	for(std::vector<std::thread>::size_type i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}

	//shut down the comms server
	commServ.join();
	run_comms = 0;

	//shut down the node server
	if (pclose(node_server) != 0){
		std::cout << "error@nodeServer: shutting down" << std::endl;
		exit(1);
	}
}

double Environment::getTime()
{
	return time(nullptr);
}

double Environment::getData(std::string type, double x, double y, double z)
{
	return data[type][(int)std::round(x)][(int)std::round(y)][(int)std::round(z)];
}
