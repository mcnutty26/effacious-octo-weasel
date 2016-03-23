///AODV route error message

#include "Aodv_rerr.hpp"

Aodv_rerr::Aodv_rerr(std::string dst_ip, int dst_seq, int ttl): Aodv_message(dst_ip, dst_seq, ttl){
}

///Returns a string representation of the message
std::string Aodv_rerr::to_string(){
	std::string result = Aodv_message::serialize();
	result = "RERR;" + result;
	return result;
}
