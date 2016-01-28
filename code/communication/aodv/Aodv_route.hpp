#ifndef EOW_AODV_ROUTE
	#define EOW_AODV_ROUTE

	#include <string>

	class Aodv_route{
		public:
			Aodv_route(int, int, std::string, int);

			int get_dst_seq();
			int get_hop_count();
			std::string get_next_hop();
			int get_life_time();
		private:
			int dst_seq;
			int hop_count;
			std::string next_hop;
			int life_time;
	};
#endif
