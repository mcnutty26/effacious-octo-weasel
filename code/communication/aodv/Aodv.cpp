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
			//TODO: throw an exception
			std::cout << "AODV was passed a non-AODV message!" << std::endl;
	}
}

Aodv_message deserialize_message(*std::string message){
	std::string dest_ip, dest_seq, ttl_string;
	int ttl;

	std::getline(&message, dest_ip, ';');
	std::getline(&message, dest_seq, ';');
	std::getline(&message, ttl_string, ';');

	ttl = int (ttl_string);
	Aodv_message result = new Aodv_message(dest_ip, dest_seq, ttl);
	
	return result;
}
	
Aodv_rreq deserialize_rreq(std::string message){
	Aodv_message base_message = deserialize_message(&message);

	std::string hop_count_string, rreq_id_string, source_ip, source_seq_string;
	int hop_count, rreq_id, source_seq;
	
	std::getline(message, hop_count_string, ';');
	std::getline(message, rreq_id_string, ';');
	std::getline(message, source_ip, ';');
	std::getline(message, source_seq, ';');

	hop_count = int (hop_count_string);
	rreq_id = int (rreq_id_string);
	source_seq = int (source_seq_string);
	Aodv_rreq result = new Aodv_rreq(hop_count, rreq_id, source_ip, base_message.get_dest_ip(), 
		source_seq, base_message.get_dest_seq(), base_message.get_ttl());

	return result;
}

Aodv_rrep deserialize_rrep(std::string message){
	Aodv_message base_message = deserialize_message(&message);

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

Aodv_rerr deserialize_rerr(std::string message){
	Aodv_message base_message = deserialize_message(&message);
	
	Aodv_rerr result = new Aodv_rerr(base_message.get_dest_ip(), base_message.get_dest_seq(), base_message.get_ttl());

	return result;
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

