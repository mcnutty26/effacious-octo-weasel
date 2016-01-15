#include <string>
#include "../../simulation/Message.hpp"

class Aodv_message: public Message{
	public:
		Aodv_message(std::string dest_ip, int dest_seq, int ttl);
		std::string get_dest_ip();
		int get_dest_seq();
	private:
		std::string dest_ip;
		int dest_seq;
}
