#include "Aodv_message.hpp"

Aodv_message(std::string dst_ip, int dst_seq, int ttl_time){
    dest_ip = dst_ip;
    dest_seq = dst_seq;
    ttl = ttl_time;
    using Message::Mesage();
}

std::string get_dest_ip(){
  return dest_ip;
}

std::string serialize(){
	std::string result;
	result = dest_ip + "," + std::to_string(dest_seq) + "," + std::to_string(ttl);
	return result;
}

int get_dest_seq(){
  return dest_seq;
}
