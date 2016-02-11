#include "Aodv.hpp"
#include <iostream>
#include <sstream>

Aodv::Aodv(Environment* env, std::string ip): CommMod(env){
	ip_address = ip;
	environment = env;
	RANGE = 10;
	route_table = *(new std::map<std::string, Aodv_route*>);
	current_message = "NULL";
	xpos = messageable->getX();
	ypos = messageable->getY();
	zpos = messageable->getZ();
	HELLO_INTERVAL = 0;
	SEQUENCE_NUMBER = 1;
	ACTIVE_ROUTE_TIMEOUT = 0;
	PATH_DISCOVERY_TIME = 0;
	BROADCAST_ID = 0;
	std::cout << "aodv: init complete" << std::endl;
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
	std::cout << "aodv: creating hello rreq" << std::endl;
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
	std::cout << "aodv: created rreq to " << dst_ip << std::endl;
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
	int dst_seq = 0;//route_table[dest_ip].sequence_number
	int life_time = 0;

	Aodv_rrep* to_send = new Aodv_rrep(hop, ip_address, dst_ip, dst_seq, life_time, ttl);
	std::cout << "aodv: created rrep to " << dst_ip << std::endl;
	return to_send;
}

Aodv_rerr* Aodv::create_rerr(std::string dst_ip, int ttl){
	int dst_seq = 0;//lookup

	Aodv_rerr* to_send = new Aodv_rerr(dst_ip, dst_seq, ttl);
	return to_send;
}

void Aodv::add_route(std::string ip, int dest_seq, int hop_count, std::string next_hop, int lifetime){
	Aodv_route* route = new Aodv_route(dest_seq, hop_count, next_hop, lifetime);
	route_table.insert(std::pair<std::string, Aodv_route*>(ip, route));
}

void Aodv::process_rreq(Aodv_rreq* message){
	//do we know about the sender?
	if (have_route(message->get_source_ip()) && message->get_source_seq() > route_table[message->get_source_ip()]->get_seq()){
		//our info is out of date, so update it
		route_table.erase(message->get_source_ip());
		add_route(message->get_source_ip(), message->get_dest_seq(), 1, message->get_source_ip(), ACTIVE_ROUTE_TIMEOUT);
		std::cout << "aodv: updated info for " << message->get_source_ip() << std::endl;
	} else if (!have_route(message->get_source_ip())) {
		//our info is missing, so create it
		add_route(message->get_source_ip(), message->get_dest_seq(), 1, message->get_source_ip(), ACTIVE_ROUTE_TIMEOUT);
		std::cout << "aodv: created info for " << message->get_source_ip() << std::endl;
	}
	
	//do we know about the destination?
	if (have_route(message->get_dest_ip()) && message->get_dest_seq() <= route_table[message->get_dest_ip()]->get_seq()){
		//our information is up to date, so return it
		Aodv_rrep* route_data = create_rrep(message->get_source_ip(), message->get_hop_count());
		environment->broadcast(route_data->to_string(), xpos, ypos, zpos, RANGE);
	} else {
		//our information is missing or old, so forward the request
	}
}

void Aodv::process_rrep(Aodv_rrep* message){
//hop count src ip life time
	(void)message;
}

void Aodv::process_rerr(Aodv_rerr* message){
	(void)message;
}

void Aodv::comm_function(){
	while (true){
		while (!inQueue.empty()){
			//get the message from the environment
			std::string message = inQueue.front();
			inQueue.pop();

			//determine what type of message it is
			std::string m_type = Aodv::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

			if (m_type == "RREQ"){
				std::cout << "aodv: rec'd a RREQ packet" << std::endl;
				process_rreq(deserialize_rreq(message));
			} else if (m_type == "RREP"){
				std::cout << "aodv: rec'd a RREP packet" << std::endl;
				process_rrep(deserialize_rrep(message));
			} else if (m_type == "RERR"){
				std::cout << "aodv: rec'd a RERR packet" << std::endl;
				process_rerr(deserialize_rerr(message));
			} else {
				std::cout << "Throw an exception - what the hell kind of a message is this?!" << std::endl;
			}
		}
		while (!outQueue.empty() && current_message == "NULL"){
			//get the message from the messageable if we are not currently processing a message
			Message* message = outQueue.front();
			std::string content = message->to_string();

			if (content == "KILL"){
				//exit if our messageable sent us a kill packet
				std::cout << "aodv: exiting" << std::endl;
				return;
			}

			outQueue.pop();

			//record that we have started to proces this message
			current_message = content;
			std::cout << "aodv: started for message " << content << std::endl;

			//create hello to determine neighbours
			Aodv_rreq* hello = create_hello();

			//send hello packet
			environment->broadcast(hello->to_string(), xpos, ypos, zpos, RANGE);
		}
	}
}

