#ifndef EOW_AODV_RREQ
	#define EOW_AODV_RREQ

	#include <string>
	#include "Aodv_message.hpp"

	class Aodv_rreq: public Aodv_message {
		public:
			Aodv_rreq(int hop, std::string src_ip, std::string dst_ip, int src_seq, int dst_seq, int ttl);
			int get_hop_count();
			std::string get_source_ip();
			std::string to_string();
			int get_source_seq();
		private:
			int hop_count;
			std::string source_ip;
			int source_seq;
	};
#endif
