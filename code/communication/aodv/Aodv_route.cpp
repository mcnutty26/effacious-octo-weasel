#include "Aodv_route.hpp"
#include <iostream>

Aodv_route::Aodv_route(int dest_seq, int hop_cnt, std::string nxt_hop, int life){
	dst_seq = dest_seq;
	hop_count = hop_cnt;
	next_hop = nxt_hop;
	life_time = life;
}

int Aodv_route::get_seq(){
	return dst_seq;
}

int Aodv_route::get_hop(){
	return hop_count;
}

std::string Aodv_route::get_next_hop(){
	return next_hop;
}

int Aodv_route::get_life(){
	return life_time;
}
