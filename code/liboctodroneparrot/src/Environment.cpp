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

std::atomic_flag lock_broadcast = ATOMIC_FLAG_INIT;
int run_comms = 1;
FILE* node_server;

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
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

Drone* Environment::getDrone(){
	return drones[0];
}

///Listens for communications from other drones
void commServer(int* flag, Environment* env){
	while(flag){
		int sockfd, newsockfd, portno;
		socklen_t clilen;
		char buffer[256];
		struct sockaddr_in serv_addr, cli_addr;
		int n;
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) {
			std::cout << "error@commServer: opening socket" << std::endl;
			exit(1);
		}
		bzero((char *) &serv_addr, sizeof(serv_addr));
		portno = 8080;
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);
		if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
			std::cout << "error@commServer: binding" << std::endl;
			exit(1);
		}
		std::cout << "init@commServer: listening on port 8080" << std::endl;
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) {
			std::cout << "error@commServer: accept connection" << std::endl;
			exit(1);
		}
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0) {
			std::cout << "error@commServer: reading from socket" << std::endl;
			exit(1);
		}
		printf("message@commServer: %s\n",buffer);
		std::string message = buffer;
		env->getDrone()->receive_message(message);
		close(newsockfd);
		close(sockfd);
	}
}

Environment::Environment(std::map<std::string, data_type> sensor_data, std::function <std::string(std::string)> nfun, double timestep)
:noiseFun(nfun)
{
	timeStep = timestep;
	data = sensor_data;
	baseStation = NULL;
	startNode();
	std::thread(&commServer, &run_comms, this).join();
};

Environment::Environment(std::map<std::string, data_type> sensor_data, double timestep)
{
	timeStep = timestep;
	data = sensor_data;
	noiseFun = &passStr;
	baseStation = NULL;
	startNode();
	std::thread(&commServer, &run_comms, this).join();
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

//thread safe (I hope) may be a little slow though... meh, it'll be fine (again... I hope)
void Environment::broadcast(std::string message, double xOrigin, double yOrigin, double zOrigin, double range, CommMod* caller)
{
	std::string nMessage = noiseFun(message);
	while(lock_broadcast.test_and_set()){}

	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	struct in_addr addr;
	char buffer[256];

	portno = 8080;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		std::cout << "error@commServer: opening socket (client)" << std::endl;
		exit(1);
	}
	inet_aton("10.0.0.255", &addr);
	server = gethostbyaddr(&addr, sizeof(addr), AF_INET);
	if (server == NULL) {
		std::cout << "error@commServer: no such host (client)" << std::endl;
		exit(1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
		std::cout << "error@commServer: connecting (client)" << std::endl;
	}
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	n = write(sockfd,message.c_str(),strlen(buffer));
	if (n < 0){
		std::cout << "error@commServer: writing to socket (client)" << std::endl;
		exit(1);
	}
	close(sockfd);

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
