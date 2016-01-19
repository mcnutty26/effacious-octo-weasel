#include "Aodv_rerr.hpp"

Aodv_rerr(std::string dst_ip, int dst_seq, int ttl){
	using Aodv_message::Aodv_message(dest_ip, dest_seq, ttl);
}

std::string serialize(){
	std::string result = Aodv_message::serialze();
	result = "RERR;" + result;
	return result;
}
