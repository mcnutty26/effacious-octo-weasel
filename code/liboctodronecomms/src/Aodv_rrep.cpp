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

///Aodv route reply message

#include "Aodv_rrep.hpp"

Aodv_rrep::Aodv_rrep(int hop_count, std::string source_ip, std::string dest_ip, std::string last_hop, int dest_seq, int life_time, int ttl, std::string next_hop): Aodv_message(dest_ip, dest_seq, ttl){
	m_hop_count = hop_count;
	m_source_ip = source_ip;
	m_life_time = life_time;
	m_last_hop = last_hop;
	m_next_hop = next_hop;
}

///Getter method for the hop count of the message
int Aodv_rrep::get_hop_count(){
	return m_hop_count;
}

///Getter method for the IP address of the sending node
std::string Aodv_rrep::get_source_ip(){
	return m_source_ip;
}

///Getter method for the life time of the route
int Aodv_rrep::get_life_time(){
	return m_life_time;
}

///Getter method for te last hop on this route
std::string Aodv_rrep::get_last_hop(){
	return m_last_hop;
}

///Getter method for the next hop on this route
std::string Aodv_rrep::get_next_hop(){
	return m_next_hop;
}

///Returns a string representation of the message
std::string Aodv_rrep::to_string(){
	std::string result = Aodv_message::serialize();
	result = "RREP;" + result;
	result += ";" + std::to_string(m_hop_count) + ";" + m_source_ip + ";" + std::to_string(m_life_time) + ";" + m_last_hop + ";" + m_next_hop;
	return result;
}
