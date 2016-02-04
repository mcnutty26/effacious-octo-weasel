#include "Aodv.hpp"
#include <iostream>
#include <sstream>

Aodv::Aodv(Environment* env, std::string ip): CommMod(env){
	ip_address = ip;
	environment = env;
	RANGE = 10;
	route_table.insert(std::pair<std::string, Aodv_route*>("192.168.0.1", new Aodv_route(0, 0, "q", 0)));
}

void Aodv::init(){
	HELLO_INTERVAL = 0;
	SEQUENCE_NUMBER = 0;
	ACTIVE_ROUTE_TIMEOUT = 0;
	PATH_DISCOVERY_TIME = 0;
	BROADCAST_ID = 0;
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
	return Aodv::create_rreq(Aodv::ip_address, 1);
}

Aodv_rreq* Aodv::create_rreq(std::string dst_ip, int ttl){
	int hop = 0;
	int dst_seq = route_table[dst_ip]->get_dst_seq();
	BROADCAST_ID++;

	Aodv_rreq* to_send = new Aodv_rreq(hop, BROADCAST_ID, ip_address, dst_ip, SEQUENCE_NUMBER, dst_seq, ttl);
	return to_send;
}

Aodv_rrep* Aodv::create_rrep(std::string dst_ip, int ttl){
	int hop = 0;
	int dst_seq = 0;//route_table[dest_ip].sequence_number
	int life_time = 0;

	Aodv_rrep* to_send = new Aodv_rrep(hop, ip_address, dst_ip, dst_seq, life_time, ttl);
	return to_send;
}

Aodv_rerr* Aodv::create_rerr(std::string dst_ip, int ttl){
	int dst_seq = 0;//lookup

	Aodv_rerr* to_send = new Aodv_rerr(dst_ip, dst_seq, ttl);
	return to_send;
}

void Aodv::process_rreq(Aodv_rreq* message){
	(void)message;
}

void Aodv::process_rrep(Aodv_rrep* message){
	(void)message;
}

void Aodv::process_rerr(Aodv_rerr* message){
	(void)message;
}

void Aodv::comm_function(){
	while (!inQueue.empty()){
		//get the message from the queue
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
		} else {
			std::cout << "Throw an exception - what the hell kind of a message is this?!" << std::endl;
		}
			
	}
	while (outQueue.empty()){
		//TODO turn into string and figure out where it's going
		//and if we have a route there etc.
		Message* message = outQueue.front();
		outQueue.pop();

		double xpos = messageable->getX();
		double ypos = messageable->getY();;
		double zpos = messageable->getZ();

		environment->broadcast(message->to_string(), xpos, ypos, zpos, RANGE);
	}
}

