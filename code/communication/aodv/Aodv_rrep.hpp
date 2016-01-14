#include <string>

class Aodv_rrep: public Aodv_message {
	public:
		Aodv_rrep(int hop, int id, std::string src_ip, std::string dst_ip, int dst_seq, int life);
    int get_hop_count();
    int get_rreq_id();
    std::string get_source_ip();
    int get_life_time();
  private:
		int hop_count;
		int rreq_id;
		std::string source_ip;
		int life_time;
}
