#include "Aodv.hpp"
#include <iostream>
#include <sstream>

Aodv::Aodv(Environment* env): CommMod(env){
	std::string ip_address = "qq";
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

/*Aodv_rreq Aodv::deserialize_rreq(std::string message){
	Aodv_message base_message = deserialize_message(&message);

	std::string hop_count_string, rreq_id_string, source_ip, source_seq_string;
	int hop_count, rreq_id, source_seq;
	
	std::stringstream mess;
	mess.str(&message);
	std::getline(mess, hop_count_string, ';');
	std::getline(mess, rreq_id_string, ';');
	std::getline(mess, source_ip, ';');
	std::getline(mess, source_seq, ';');

	hop_count = int (hop_count_string);
	rreq_id = int (rreq_id_string);
	source_seq = int (source_seq_string);
	Aodv_rreq result = new Aodv_rreq(hop_count, rreq_id, source_ip, base_message.get_dest_ip(), 
		source_seq, base_message.get_dest_seq(), base_message.get_ttl());

	return result;
}
*/
Aodv_rrep Aodv::deserialize_rrep(std::string message){
	std::string dest_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int dest_seq = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int ttl = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

	std::string hop_count_string, source_ip, life_time_string;
	int hop_count, life_time;
	
	std::getline(message, hop_count_string, ';');
	std::getline(message, source_ip, ';');
	std::getline(message, life_time_string, ';');

	hop_count = int (hop_count_string);
	life_time = int (life_time_string);
	Aodv_rrep result = new Aodv_rrep(hop_count, source_ip, base_message.get_dest_ip(), base_message.get_dest_seq(),
		life_time, base_message.get_ttl());

	return result;
}

Aodv_rerr* Aodv::deserialize_rerr(std::string message){
	std::string dest_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int dest_seq = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int ttl = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	
	Aodv_rerr* result = new Aodv_rerr(dest_ip, dest_seq, ttl);

	return result;
}

Aodv_rreq* Aodv::create_hello(){
	return Aodv::create_rreq(Aodv::ip_address, 1);
}

Aodv_rreq* Aodv::create_rreq(std::string dest_ip, int ttl){
	int hop = 0;
	int dest_seq = 0;//route_table[dest_ip].sequence_number;
	BROADCAST_ID++;

	Aodv_rreq* to_send = new Aodv_rreq(hop, BROADCAST_ID, ip_address, dest_ip, SEQUENCE_NUMBER, dest_seq, ttl);
	return to_send;
}

//Aodv_rrep Aodv::create_rrep(std::string dest_ip){
	//int hop = 0;
	//int dest_seq = route_table[dest_ip].sequence_number;

	//Aodv_rrep to_send = new Aodv_rrep(hop, ip_address, dest_ip,

//}

