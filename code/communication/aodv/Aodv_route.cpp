#include "Aodv_route.hpp"

Aodv_route::Aodv_route(std::string dst_ip, std::string nxt_ip, int ART){
	dest_ip = dst_ip;
	next_ip = nxt_ip;
	ACTIVE_ROUTE_TIMEOUT = ART;
}

std::string Aodv_route::get_dest_ip(){
	return dest_ip;
}

std::string Aodv_route::get_next_ip(){
	return next_ip;
}

int Aodv_route::get_timeout(){
	return ACTIVE_ROUTE_TIMEOUT;
}
