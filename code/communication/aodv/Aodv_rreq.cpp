#include "Aodv_rreq.hpp"

Aodv_rreq::Aodv_rreq(int hop, int id, std::string src_ip, std::string dst_ip, int src_seq, int dst_seq, int ttl): Aodv_message(dst_ip, dst_seq, ttl){
	hop_count = hop;
	rreq_id = id;
	source_ip = src_ip;
	source_seq = src_seq;
}

int Aodv_rreq::get_hop_count(){
	return hop_count;
}

int Aodv_rreq::get_rreq_id(){
	return rreq_id;
}
    
std::string Aodv_rreq::get_source_ip(){
	return source_ip;
}

int Aodv_rreq::get_source_seq(){
	return source_seq;
}

std::string Aodv_rreq::to_string(){
	std::string result = Aodv_message::serialize();
	result = "RREQ;" + result;
	result += ";" + std::to_string(hop_count) + ";" + source_ip + ";"
		+ std::to_string(rreq_id) + ";" + std::to_string(source_seq);
	return result;
}
