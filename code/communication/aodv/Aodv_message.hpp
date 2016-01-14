#include <string>

class Aodv_message{
	public:
		Aodv_message(std::string dest_ip, int dest_seq);
	private:
		std::string dest_ip;
		int dest_seq;
		int time_stamp;
}
