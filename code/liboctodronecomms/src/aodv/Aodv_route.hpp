#ifndef EOW_AODV_ROUTE
	#define EOW_AODV_ROUTE

	#include <string>

	class Aodv_route{
		public:
			Aodv_route(int, int, std::string, int);

			int get_seq();
			int get_hop();
			std::string get_next_hop();
			int get_life();
		private:
			///Sequence number of the route destination
			int dst_seq;
			///Number of hops required to get to the destination node
			int hop_count;
			///Next hop on this route
			std::string next_hop;
			///Lifetime of this route
			int life_time;
	};
#endif
