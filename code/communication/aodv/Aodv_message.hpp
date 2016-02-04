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
			std::string dest_ip;
			int dest_seq;
			int ttl;
	};
#endif
