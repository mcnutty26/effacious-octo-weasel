#include "Aodv_rrep.hpp"

Aodv_rrep::Aodv_rrep(int hop_count, std::string source_ip, std::string dest_ip, std::string last_hop, int dest_seq, int life_time, int ttl, std::string next_hop): Aodv_message(dest_ip, dest_seq, ttl){
	m_hop_count = hop_count;
	m_source_ip = source_ip;
	m_life_time = life_time;
	m_last_hop = last_hop;
	m_next_hop = next_hop;
}

int Aodv_rrep::get_hop_count(){
	return m_hop_count;
}

std::string Aodv_rrep::get_source_ip(){
	return m_source_ip;
}

int Aodv_rrep::get_life_time(){
	return m_life_time;
}

std::string Aodv_rrep::get_last_hop(){
	return m_last_hop;
}

std::string Aodv_rrep::get_next_hop(){
	return m_next_hop;
}

std::string Aodv_rrep::to_string(){
	std::string result = Aodv_message::serialize();
	result = "RREP;" + result;
	result += ";" + std::to_string(m_hop_count) + ";" + m_source_ip + ";" + std::to_string(m_life_time) + ";" + m_last_hop + ";" + m_next_hop;
	return result;
}
