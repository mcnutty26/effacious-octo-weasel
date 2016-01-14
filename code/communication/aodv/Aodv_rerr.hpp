#include <string>

class Aodv_rerr: public Aodv_message {
	public:
		Aodv_rerr(std::string dst_ip, int dst_seq);
}
