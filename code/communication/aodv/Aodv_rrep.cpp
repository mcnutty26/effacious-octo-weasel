#include "Aodv_rrep.hpp"

Aodv_rrep(int hop, int id, std::string src_ip, std::string dst_ip, int dst_seq, int life){
	using Aodv_message::Aodv_message(dest_ip, dest_seq);
	hop_count = hop;
	rreq_id = id;
	source_ip = src_ip;
	life_time = life;
}
