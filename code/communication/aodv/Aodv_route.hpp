#include <string>

class Aodv_route{
	public:
		Aodv_route(dest_ip, next_ip, ACTIVE_ROUTE_TIMEOUT);
		std::string get_dest_ip();
		std::string get_dest_seq();
		int get_timeout();
	private:
		std::string dest_ip;
		std::string next_ip;
		int dest_seq;
		int ACTIVE_ROUTE_TMEOUT
};
