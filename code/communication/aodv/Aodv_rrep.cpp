#include "Aodv_rrep.hpp"

Aodv_rrep(int hop, int id, std::string src_ip, std::string dst_ip, int dst_seq, int life, int ttl){
	using Aodv_message::Aodv_message(dest_ip, dest_seq, ttl);
	hop_count = hop;
	rreq_id = id;
	source_ip = src_ip;
	life_time = life;
}

int get_hop_count(){
	return hop_count;
}

int get_rreq_id(){
	return rreq_id;
}
    
std::string get_source_ip(){
	return source_ip;
}

int get_life_time(){
	return life_time;
}

std::string serialize(){
	std::string result = Aodv_message::serialze();
	result = "RREP;" + result;
	result += ";" + std::to_string(hop_count) + ";" + std::to_string(rreq_id) + ";" 
		+ source_ip + ";" + std::to_string(life_time);
	return result;
}
