#include "Aodv.hpp"
#include <iostream>
#include <sstream>
#include "../basic/Basic_message.hpp"
#include "../basic/Basic_message_addressed.hpp"
#include <chrono>
#include <thread>

Aodv::Aodv(Environment* env, std::string ip, std::atomic_flag* flag, bool debug): CommMod(env){
	ip_address = ip;
	environment = env;
	RANGE = 50;
	route_table = *(new std::map<std::string, Aodv_route*>);
	current_message = std::pair<std::string, std::string>("", "");
	state = 0;
	HELLO_INTERVAL = 0;
	SEQUENCE_NUMBER = 1;
	ACTIVE_ROUTE_TIMEOUT = 0;
	PATH_DISCOVERY_TIME = 0;
	BROADCAST_ID = 0;
	TTL = 5;
	lock = flag;
	logging = debug;
	log("init complete");

	//state can take on the following values:
	//0 -> no current activity
	//1 -> sending message: waiting for hello replies
	//2 -> sending message: waiting for route information
	//3 -> middle node on multi hop route (forwarding RREQ)
}

std::string Aodv::get_attribute(std::string message){
	std::string attribute;
	
	std::stringstream attr;
	attr.str(message);
	std::getline(attr, attribute, ';');
	return attribute;
}

Aodv_rreq* Aodv::deserialize_rreq(std::string message){
	std::string dst_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int dst_seq = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int ttl = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

	int hop_count = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string src_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int rreq_id = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int src_seq = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

	Aodv_rreq* result = new Aodv_rreq(hop_count, rreq_id, src_ip, dst_ip, src_seq, dst_seq, ttl);

	//std::cout << dst_ip << "|" << dst_seq << "|" << ttl << "|" << hop_count << "|" << src_ip << "|" << rreq_id << "|" << src_seq << std::endl;

	return result;
}

Aodv_rrep* Aodv::deserialize_rrep(std::string message){
	std::string dst_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int dst_seq = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int ttl = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

	int hop_count = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string src_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int life_time = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	
	Aodv_rrep* result = new Aodv_rrep(hop_count, src_ip, dst_ip, dst_seq, life_time, ttl);

	return result;
}

Aodv_rerr* Aodv::deserialize_rerr(std::string message){
	std::string dst_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int dst_seq = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int ttl = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	
	Aodv_rerr* result = new Aodv_rerr(dst_ip, dst_seq, ttl);

	return result;
}

Aodv_rreq* Aodv::create_hello(){
	log("creating hello rreq");
	return Aodv::create_rreq(ip_address, 1);
}

Aodv_rreq* Aodv::create_rreq(std::string dst_ip, int ttl){
	int hop = 0;
	int dst_seq = 0;
	if (have_route(dst_ip)){
		dst_seq = route_table[dst_ip]->get_seq();
	}
	BROADCAST_ID++;

	Aodv_rreq* to_send = new Aodv_rreq(hop, BROADCAST_ID, ip_address, dst_ip, SEQUENCE_NUMBER, dst_seq, ttl);
	log("created rreq to " + dst_ip);
	return to_send;
}

bool Aodv::have_route(std::string ip){
    if (route_table.find(ip) != route_table.end()){
	return true;
    } else {
	return false;
    }
}

Aodv_rrep* Aodv::create_rrep(std::string dst_ip, int ttl){
	int hop = 0;
	int dst_seq = 0;
	if (have_route(dst_ip)){
		dst_seq = route_table[dst_ip]->get_seq();
	}
	int life_time = 0;

	Aodv_rrep* to_send = new Aodv_rrep(hop, ip_address, dst_ip, dst_seq, life_time, ttl);
	log("created rrep to " + dst_ip);
	return to_send;
}

Aodv_rerr* Aodv::create_rerr(std::string dst_ip, int ttl){
	int dst_seq = 0;
	if (have_route(dst_ip)){
		dst_seq = route_table[dst_ip]->get_seq();
	}

	Aodv_rerr* to_send = new Aodv_rerr(dst_ip, dst_seq, ttl);
	return to_send;
}

void Aodv::add_route(std::string ip, int dest_seq, int hop_count, std::string next_hop, int lifetime){
	Aodv_route* route = new Aodv_route(dest_seq, hop_count, next_hop, lifetime);
	route_table.insert(std::pair<std::string, Aodv_route*>(ip, route));
	log("Route to " + ip + " via " + next_hop);
}

void Aodv::process_rreq(Aodv_rreq* message){
	if (message->get_source_ip() == ip_address){
		return;
	} else {
		log("rec'd a RREQ packet");
	}

	//do we know about the sender?
	if (have_route(message->get_source_ip()) && message->get_source_seq() > route_table[message->get_source_ip()]->get_seq()){
		//our info is out of date, so update it
		route_table.erase(message->get_source_ip());
		add_route(message->get_source_ip(), message->get_dest_seq(), 1, message->get_source_ip(), ACTIVE_ROUTE_TIMEOUT);
		log("updated info for " + message->get_source_ip());
	} else if (!have_route(message->get_source_ip())) {
		//our info is missing, so create it
		add_route(message->get_source_ip(), message->get_dest_seq(), 1, message->get_source_ip(), ACTIVE_ROUTE_TIMEOUT);
		log("created info for " + message->get_source_ip());
	}

	if (state == 0){
	//do we know about the destination?
	if (have_route(message->get_dest_ip()) && message->get_dest_seq() <= route_table[message->get_dest_ip()]->get_seq()){
		//update internal state
		state = 0;

		//our information is up to date, so return it
		Aodv_rrep* route_data = create_rrep(message->get_source_ip(), message->get_hop_count());
		environment->broadcast(route_data->to_string(), xpos, ypos, zpos, RANGE);
		log("returned info for " + message->get_dest_ip());
	} else if (message->get_dest_ip() == ip_address){
		//we are the destination
		Aodv_rrep* route_data = create_rrep(message->get_source_ip(), message->get_hop_count());
		environment->broadcast(route_data->to_string(), xpos, ypos, zpos, RANGE);
		log("returned self info to " + message->get_source_ip());
	} else {
		//update internal state
		state = 3;

		//our information is missing or old, so forward the request
		Aodv_rreq* route_request = create_rreq(message->get_dest_ip(), message->get_ttl());
		environment->broadcast(route_request->to_string(), xpos, ypos, zpos, RANGE);
		log("forwarded request for " + message->get_dest_ip());
	}
	}
}

void Aodv::process_rrep(Aodv_rrep* message){
	if (message->get_source_ip() == ip_address){
		return;
	} else {
		log("rec'd a RREP packet");
	}
	
	//do we know about the sender?
	if (have_route(message->get_source_ip()) && message->get_dest_seq() > route_table[message->get_source_ip()]->get_seq()){
		//our info is out of date, so update it
		route_table.erase(message->get_source_ip());
		add_route(message->get_source_ip(), message->get_dest_seq(), 1, message->get_source_ip(), ACTIVE_ROUTE_TIMEOUT);
		log("updated info for " + message->get_source_ip());
	} else if (!have_route(message->get_source_ip())) {
		//our info is missing, so create it
		add_route(message->get_source_ip(), message->get_dest_seq(), 1, message->get_source_ip(), ACTIVE_ROUTE_TIMEOUT);
		log("created info for " + message->get_source_ip());
	}

	if (state == 1){
		//now we know our neighbours, send out the proper RREQ
		state = 2;
		Aodv_rreq* rreq = create_rreq(current_message.second, TTL);
		environment->broadcast(rreq->to_string(), xpos, ypos, zpos, RANGE);
	} else if (state == 2){
		//Now we have the route, send the data packet	
		state = 0;
		std::string data_message = "DATA;" + current_message.second + ";" + route_table[current_message.second]->get_next_hop()
		    + ip_address + ";" + current_message.first;
		environment->broadcast(data_message, xpos, ypos, zpos, RANGE);
		log("data packet sent");
	} else if (state == 3) {
		//We are a middle node in a multi hop route, so forward the packet
		log("forwarding RREP");
		Aodv_rrep* route_data = create_rrep(message->get_dest_ip(), 0);
		environment->broadcast(route_data->to_string(), xpos, ypos, zpos, RANGE);
	}
	
}

void Aodv::process_data(std::string message){
	std::string destination = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string next_hop = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string source = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string content = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

	if (source == ip_address){
		return;
	} else {
		log("rec'd a DATA packet from " + source);
	}

	if (destination == ip_address){
		//the message is for us!
		Message* to_push = new Basic_message(message);
		messageable->push_message(to_push);
	} else {
		//send the message 
		std::string data_message = "DATA;" + destination + ";" + route_table[destination]->get_next_hop()
		    + source + ";" + content;
		environment->broadcast(data_message, xpos, ypos, zpos, RANGE);
		log("Forwarded data packet");
	}
}

void Aodv::process_rerr(Aodv_rerr* message){
	log("rec'd a RERR packet");
	(void)message;
}

void Aodv::comm_function(){
	while (true){
		while (!inQueue.empty()){
			//update our position in 3d space
			xpos = messageable->getX();
			ypos = messageable->getY();
			zpos = messageable->getZ();
			
			//get the message from the environment
			std::string message = inQueue.front();
			inQueue.pop();

			//determine what type of message it is
			std::string m_type = Aodv::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

			if (m_type == "RREQ"){
				process_rreq(deserialize_rreq(message));
			} else if (m_type == "RREP"){
				process_rrep(deserialize_rrep(message));
			} else if (m_type == "RERR"){
				process_rerr(deserialize_rerr(message));
			} else if (m_type == "DATA"){
				process_data(message);
			} else {
				log("Throw an exception - what the hell kind of a message is this?!");
			}
		}
		while (!outQueue.empty() && state == 0){
			//update our position in 3d space
			xpos = messageable->getX();
			ypos = messageable->getY();
			zpos = messageable->getZ();
			
			//get the message from the messageable if we are not currently processing a message
			std::string message = outQueue.front()->to_string();
			std::string address = Aodv::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
			std::string content = Aodv::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

			if (content == "KILL"){
				//exit if our messageable sent us a kill packet
				log("exiting");
				return;
			}

			outQueue.pop();

			//record that we have started to proces this message
			current_message = std::pair<std::string, std::string>(content, address);
			log("started for message " + content);

			//create hello to determine neighbours
			Aodv_rreq* hello = create_hello();

			//update internal state
			state = 1;

			//send hello packet
			environment->broadcast(hello->to_string(), xpos, ypos, zpos, RANGE);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Aodv::log(std::string log_message){
	if (logging){
		while(lock->test_and_set()){}
		std::cout << "aodv@" << ip_address << ": " << log_message << std::endl;
		lock->clear();
	}
}

