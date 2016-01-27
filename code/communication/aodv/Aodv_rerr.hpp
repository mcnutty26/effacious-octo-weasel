#ifndef EOW_AODV_RERR
	#define EOW_AODV_RERR

	#include <string>

	class Aodv_rerr: public Aodv_message {
		public:
			Aodv_rerr(std::string dst_ip, int dst_seq, int ttl);
			std::string to_string();
	};
#endif
