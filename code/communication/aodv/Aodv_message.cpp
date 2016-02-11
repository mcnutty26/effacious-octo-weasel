#include "Aodv_message.hpp"

Aodv_message::Aodv_message(std::string dst_ip, int dst_seq, int ttl_time): Message("AODV"){
    dest_ip = dst_ip;
    dest_seq = dst_seq;
    ttl = ttl_time;
}

std::string Aodv_message::get_dest_ip(){
  return dest_ip;
}

int Aodv_message::get_ttl(){
    return ttl;
}

int Aodv_message::get_dest_seq(){
  return dest_seq;
}

std::string Aodv_message::serialize(){
	std::string result;
	result = dest_ip + ";" + std::to_string(dest_seq) + ";" + std::to_string(ttl);
	return result;
}
