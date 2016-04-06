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

///AODV route request message

#include "Aodv_rreq.hpp"

Aodv_rreq::Aodv_rreq(int hop, std::string src_ip, std::string dst_ip, int src_seq, int dst_seq, int ttl): Aodv_message(dst_ip, dst_seq, ttl){
	hop_count = hop;
	source_ip = src_ip;
	source_seq = src_seq;
}

///Getter method for the hop count of the message
int Aodv_rreq::get_hop_count(){
	return hop_count;
}

///Getter method for the IP address of the sending node
std::string Aodv_rreq::get_source_ip(){
	return source_ip;
}

///Getter method for the sequence number of the sending node
int Aodv_rreq::get_source_seq(){
	return source_seq;
}

///Returns a string representation of the message
std::string Aodv_rreq::to_string(){
	std::string result = Aodv_message::serialize();
	result = "RREQ;" + result;
	result += ";" + std::to_string(hop_count) + ";" + source_ip + ";"
		+ std::to_string(source_seq);
	return result;
}
