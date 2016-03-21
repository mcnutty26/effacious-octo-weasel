#ifndef EOW_AODV_MESSAGE
	#define EOW_AODV_MESSAGE

	#include <string>
	#include <Message.hpp>

	class Aodv_message: public Message{
		public:
			Aodv_message(std::string, int, int);
			std::string get_dest_ip();
			std::string serialize();
			int get_dest_seq();
			int get_ttl();
		private:
			///The IP address of the detination node
			std::string dest_ip;
			///The sequence number of the destination node
			int dest_seq;
			///The time to live of the message
			int ttl;
	};
#endif
