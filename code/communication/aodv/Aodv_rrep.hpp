#include <string>

class Aodv_rrep: public Aodv_message {
	public:
		Aodv_rrep(int hop, int id, std::string src_ip, std::string dst_ip, int dst_seq, int life);
		int hop_count;
		int rreq_id;
		std::string source_ip;
		int life_time;
}
