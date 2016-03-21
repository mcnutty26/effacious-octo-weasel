#ifndef EOW_AODV_RREP
	#define EOW_AODV_RREP

	#include <string>
	#include "Aodv_message.hpp"

	class Aodv_rrep: public Aodv_message {
		public:
			Aodv_rrep(int, std::string, std::string, std::string, int, int, int, std::string);
			int get_hop_count();
			std::string get_source_ip();
			std::string to_string();
			int get_life_time();
			std::string get_last_hop();
			std::string get_next_hop();
		private:
			///Number of hops required to get from the source to the destination of the route
			int m_hop_count;
			///IP address of the node at which the route terminates
			std::string m_source_ip;
			///Time for which this route is valid
			int m_life_time;
			///The last node which forwarded this reply
			std::string m_last_hop;
			///The next node to which this reply will be forwarded
			std::string m_next_hop;
	};
#endif
