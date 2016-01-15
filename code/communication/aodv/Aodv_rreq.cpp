#include "Aodv_rreq.hpp"

Aodv_rreq(int hop, int id, std::string src_ip, std::string dst_ip, int src_seq, int dst_seq){
	using Aodv_message::Aodv_message(dest_ip, dest_seq);
	hop_count = hop;
	rreq_id = id;
	source_ip = src_ip;
	source_seq = src_seq;
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

int get_source_seq(){
	return source_seq;
}
