/*
This file is part of octoDrone.

octoDrone is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

octoDrone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with octoDrone.  If not, see <http://www.gnu.org/licenses/>.
*/

///Entry in ann AODV routing table

#include "Aodv_route.hpp"
#include <iostream>

Aodv_route::Aodv_route(int dest_seq, int hop_cnt, std::string nxt_hop, int life){
	dst_seq = dest_seq;
	hop_count = hop_cnt;
	next_hop = nxt_hop;
	life_time = life;
}

///Getter method for the sequence number of the route destination
int Aodv_route::get_seq(){
	return dst_seq;
}

///Getter method for the route hop count
int Aodv_route::get_hop(){
	return hop_count;
}

///Getter method for the next hop on this route
std::string Aodv_route::get_next_hop(){
	return next_hop;
}

///Getter method for the route life time
int Aodv_route::get_life(){
	return life_time;
}
