#include "Aodv.hpp"

Aodv(Environment* env, std::string ip){
	using Aodv_message::Aodv_message(env, ip_address);
	ip_address = ip;
}

void init(){
	HELLO_INTERVAL = 0;
	SEQUENCE_NUMBER = 0;
	ACTIVE_ROUTE_TIMEOUT = 0;
	PATH_DISCOVERY_TIME = 0;
	BROADCAST_ID = 0;
}

Aodv_message create_hello(){
	return create_rreq(ip_address, 1);
}

Aodv_message create_rreq(std::string dest_ip, int ttl){
	int hop = 0;
	int dest_seq = route_table[dest_ip].sequence_number;
	BROADCAST_ID++;

	Aodv_rreq to_send = new Aodv_rreq(hop, BROADCAST_ID, ip_address, dest_ip, SEQUENCE_NUMBER, dest_seq, ttl);
	return to_send;
}

Aodv_message create_rrep(std::string dest_ip){
	int hop = 0;
	int dest_seq = route_table[dest_ip].sequence_number;

	Aodv_rrep to_send = new Aodv_rrep(hop, ip_address, dest_ip, 
}

Aodv_message deserialize(std::string message){
	std::string message_type;
	std::getline(message, message_type, ';');
	switch(message_type){
		case "RREQ":
			return deserialize_rreq(message);
		case "RREP":
			return deserialize_rrep(message);
		case "RERR":
			return deserialize_rerr(message);
		default:
			std::cout << "AODV was passed a non-AODV message!" << std::endl;
	}
}

Aodv_message deserialize_message(std::string message){
	std::string dest_ip;
	std::string dest_seq;
	std::string ttl_string;
	int ttl;

	std::getline(message, dest_ip, ';');
	std::getline(message, dest_seq, ';');
	std::getline(message, ttl_string, ';');

	ttl = int (ttl_string);
	Aodv_message result = new Aodv_message(dest_ip, dest_seq, ttl);
	
	return result;
}
	
Aodv_rreq deserialize_rreq(std::string message){
	std::string message_copy = message;
	Aodv_message base_message = deserialize_message(message);
}

Aodv_rrep deserialize_rrep(std::string message){
}

Aodv_rerr deserialize_rerr(std::string message){
}
