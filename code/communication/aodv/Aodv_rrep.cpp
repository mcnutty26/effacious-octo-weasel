#include "Aodv_rrep.hpp"

Aodv_rrep::Aodv_rrep(int hop, std::string src_ip, std::string dst_ip, int dst_seq, int life, int ttl): Aodv_message(dst_ip, dst_seq, ttl){
	hop_count = hop;
	source_ip = src_ip;
	life_time = life;
}

int Aodv_rrep::get_hop_count(){
	return hop_count;
}

std::string Aodv_rrep::get_source_ip(){
	return source_ip;
}

int Aodv_rrep::get_life_time(){
	return life_time;
}

std::string Aodv_rrep::to_string(){
	std::string result = Aodv_message::serialize();
	result = "RREP;" + result;
	result += ";" + std::to_string(hop_count) + ";" + source_ip + ";" + std::to_string(life_time);
	return result;
}
