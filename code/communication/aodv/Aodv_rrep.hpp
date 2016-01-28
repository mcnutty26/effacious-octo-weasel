#ifndef EOW_AODV_RREP
	#define EOW_AODV_RREP

	#include <string>
	#include "Aodv_message.hpp"

	class Aodv_rrep: public Aodv_message {
		public:
			Aodv_rrep(int, std::string, std::string, int, int, int);
			int get_hop_count();
			std::string get_source_ip();
			std::string to_string();
			int get_life_time();
		private:
			int hop_count;
			std::string source_ip;
			int life_time;
	};
#endif
