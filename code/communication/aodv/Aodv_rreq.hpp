#include <string>

class Aodv_rreq: public Aodv_message {
	public:
		Aodv_rreq(int hop, int id, std::string src_ip, std::string dst_ip, int src_seq, int dst_seq);
	private:
		int hop_count;
		int rreq_id;
		std::string source_ip;
		int source_seq;
}
