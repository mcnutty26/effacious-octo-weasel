#include "Aodv.hpp"
#include <iostream>
#include <sstream>
//#include "../basic/Basic_message.hpp"
#include "../basic_addressed/Basic_message_addressed.hpp"
#include <chrono>
#include <thread>

Aodv::Aodv(Environment* env, std::string ip, std::atomic_flag* flag, bool debug): CommMod(env){
	ip_address = ip;
	environment = env;
	RANGE = 50;
	route_table = *(new std::map<std::string, Aodv_route*>);
	current_message = std::pair<std::string, std::string>("", "");
	state = 0;
	HELLO_INTERVAL = 2500;
	last_hello = -HELLO_INTERVAL;
	SEQUENCE_NUMBER = 1;
	ACTIVE_ROUTE_TIMEOUT = 5000;
	PATH_DISCOVERY_TIME = 5;
	BROADCAST_ID = 0;
	TTL = 5;
	lock = flag;
	logging = debug;
	log("init complete");

	//state can take on the following values:
	//0 -> no current activity
	//1 -> sending message: waiting for route information
	//2 -> middle node on multi hop route (forwarded RREQ, waiting for RREP)
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
	int src_seq = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

	Aodv_rreq* result = new Aodv_rreq(hop_count, src_ip, dst_ip, src_seq, dst_seq, ttl);
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
	std::string lst_hop = Aodv::get_attribute(message).c_str();
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string nxt_hop = Aodv::get_attribute(message).c_str();
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	
	Aodv_rrep* result = new Aodv_rrep(hop_count, src_ip, dst_ip, lst_hop, dst_seq, life_time, ttl, nxt_hop);
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
	return Aodv::create_rreq(ip_address, ip_address, 1);
}

Aodv_rreq* Aodv::create_rreq(std::string dst_ip, std::string src_ip, int ttl){
	int hop = 0;
	int dst_seq = 0;
	if (have_route(dst_ip)){
		dst_seq = route_table[dst_ip]->get_seq();
	}

	Aodv_rreq* to_send = new Aodv_rreq(hop, src_ip, dst_ip, SEQUENCE_NUMBER, dst_seq, ttl);
	return to_send;
}

bool Aodv::have_route(std::string ip){
	if (route_table.find(ip) != route_table.end()){// && route_table[ip]->get_life() + ACTIVE_ROUTE_TIMEOUT < environment->getTime()){
		return true;
	} else {
		return false;
	}
}

Aodv_rrep* Aodv::create_rrep(std::string dst_ip, std::string src_ip, int ttl){
	int hop = 0;
	int dst_seq = route_table[dst_ip]->get_seq();
	int life_time = 0;
	std::string next_hop = route_table[dst_ip]->get_next_hop();

	Aodv_rrep* to_send = new Aodv_rrep(hop, src_ip, dst_ip, ip_address, dst_seq, life_time, ttl, next_hop);
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

void Aodv::add_route(std::string ip, int dest_seq, int hop_count, std::string next_hop){
	Aodv_route* route = new Aodv_route(dest_seq, hop_count, next_hop, ACTIVE_ROUTE_TIMEOUT);
	route_table.insert(std::pair<std::string, Aodv_route*>(ip, route));
	log("ADDED " + ip + " VIA " + next_hop);
}

void Aodv::process_rreq(Aodv_rreq* message){
	log("rec'd a RREQ packet from " + message->get_source_ip() + " for " + message->get_dest_ip());

	//process hello messages
	if (message->get_source_ip() == message->get_dest_ip()){
		if (have_route(message->get_source_ip()) && message->get_source_seq() > route_table[message->get_source_ip()]->get_seq()){
			//our info is out of date, so update it
			route_table.erase(message->get_source_ip());
			add_route(message->get_source_ip(), message->get_dest_seq(), 1, message->get_source_ip());
			log("updated info for " + message->get_source_ip());
		} else if (!have_route(message->get_source_ip())) {
			//our info is missing, so create it
			add_route(message->get_source_ip(), message->get_dest_seq(), 1, message->get_source_ip());
			log("created info for " + message->get_source_ip());
		}
		Aodv_rrep* route_data = create_rrep(message->get_source_ip(), message->get_dest_ip(), message->get_hop_count());
		broadcast(route_data->to_string());
		log("Replied to hello message from " + message->get_source_ip());
	} else if (state == 0){
		state = 2;
		if (have_route(message->get_dest_ip())){
			Aodv_rrep* route_data = create_rrep(message->get_source_ip(), ip_address, TTL);
			log("Answering  multihop route request from " + message->get_source_ip());
			broadcast(route_data->to_string());
		} else if (message->get_source_ip() != current_message.second){
			Aodv_rreq* route_data = create_rreq(message->get_dest_ip(), ip_address, message->get_ttl() - 1);
			current_message.second = message->get_source_ip();
			log("Forwarding multihop route request from " + message->get_source_ip() + " to " + message->get_dest_ip());
			broadcast(route_data->to_string());
		}
	}
}

void Aodv::process_rrep(Aodv_rrep* message){
	log("rec'd a RREP packet from " + message->get_source_ip() + " / " + message->get_last_hop());

	//check our info on the sender
	if (false){
		//our info is out of date, so update it
		route_table.erase(message->get_source_ip());
		add_route(message->get_source_ip(), message->get_dest_seq(), 1, (message->get_last_hop()));
		log("updated info for " + message->get_source_ip());
	} else if (!have_route(message->get_source_ip()) && message->get_source_ip() != ip_address) {
		//our info is missing, so create it
		std::string last_hop = (message->get_source_ip() == ip_address ? ip_address : message->get_last_hop());
		add_route(message->get_source_ip(), message->get_dest_seq(), 1, last_hop);
		log("created info for " + message->get_source_ip());
	}

	if(state == 1 && message->get_dest_ip() == ip_address && message->get_source_ip() != ip_address){
		//we were waiting for a route
		state = 0;
		std::string data_message = "DATA;" 
			+ current_message.second;
			+ ";" + route_table[current_message.second]->get_next_hop()
			+ ";" + ip_address 
			+ ";" + current_message.first;
		broadcast(data_message);
		log("Data packet sent via " + route_table[current_message.second]->get_next_hop());
		
	} else if (state == 2 && current_message.second == message->get_dest_ip()){
		//we previously forwarded a multihop route request
		Aodv_rrep* route_info = create_rrep(message->get_source_ip(), message->get_dest_ip(), message->get_ttl() - 1);
		broadcast(route_info->to_string());
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

	log("rec'd a DATA packet from " + source + ", via " + next_hop);
	log("dest " + destination + " nxt " + next_hop + " src " + source + " con " + content);

	if (destination == ip_address){
		log("The data packet is for this node");
		state = 0;
		messageable->push_message(new Basic_message_addressed(content, source));
	} else {
		log("Forwarding data packet");
		std::string data_message = "DATA;" 
			+ destination
			+ ";" + route_table[destination]->get_next_hop()
			+ ";" + source 
			+ ";" + content;
		broadcast(data_message);
	}
}

void Aodv::process_rerr(Aodv_rerr* message){
	log("rec'd a RERR packet");
	(void)message;
}

void Aodv::comm_function(){
	while (true){
		

		if (last_hello + HELLO_INTERVAL < environment->getTime()){
			log("sending hello");
			Aodv_rreq* hello = create_hello();
			last_hello = environment->getTime();
			broadcast(hello->to_string());
		}

		while (!inQueue.empty()){
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
				log("rec'd and dropped unknown packet");
			}
		}
		while (!outQueue.empty() && state == 0){
			//get the message from the messageable if we are not currently processing a message
			std::string message = outQueue.front()->to_string();
			std::string address = Aodv::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
			std::string content = Aodv::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
			outQueue.pop();

			//exit if our messageable sent us a kill packet
			if (content == "KILL"){
				log("exiting");
				return;
			}

			log("Starting AODV for message to " + address);

			//update internal state
			state = 1;

			if (have_route(address)){
				state = 0;
				std::string data_message = "DATA;" 
					+ address
					+ ";" + route_table[address]->get_next_hop()
					+ ";" + ip_address 
					+ ";" + content;
				broadcast(data_message);
				log("data packet sent with exitsing info via " + route_table[current_message.second]->get_next_hop());
			} else {
				current_message.first = content;
				current_message.second = address;
				Aodv_rreq* route_request = create_rreq(address, ip_address, TTL);
				state = 1;
				log("Sent out a route request");
				broadcast(route_request->to_string());
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Aodv::log(std::string log_message){
	if (logging){
		while(lock->test_and_set()){}
		std::ostringstream time_stream;
		time_stream << environment->getTime();
		std::string time_string  = time_stream.str();
		std::cout << "(" + time_string + ")aodv@" << ip_address << ": " << log_message << std::endl;
		lock->clear();
	}
}

void Aodv::broadcast(std::string message){
	//Update our position
	double xpos = messageable->getX();
	double ypos = messageable->getY();
	double zpos = messageable->getZ();
	environment->broadcast(message, xpos, ypos, zpos, RANGE, this);
}

