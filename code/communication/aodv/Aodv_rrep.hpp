#include <string>

class Aodv_rrep: public Aodv_message {
	public:
		Aodv_rrep(int hop, std::string src_ip, std::string dst_ip, int dst_seq, int life, int ttl);
		int get_hop_count();
		std::string get_source_ip();
		int get_life_time();
	private:
		int hop_count;
		std::string source_ip;
		int life_time;
}
