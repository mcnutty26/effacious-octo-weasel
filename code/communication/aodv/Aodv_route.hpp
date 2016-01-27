#ifndef EOW_AODV_ROUTE
	#define EOW_AODV_ROUTE

	#include <string>

	class Aodv_route{
		public:
			Aodv_route(std::string, std::string, int);
			std::string get_dest_ip();
			std::string get_next_ip();
			int get_timeout();
		private:
			std::string dest_ip;
			std::string next_ip;
			int dest_seq;
			int ACTIVE_ROUTE_TMEOUT;
	};
#endif
