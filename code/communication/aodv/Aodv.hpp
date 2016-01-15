#include <string>
#include <map>

class Aodv: public CommMod {
	public:
		Aodv(Environment* env, std::string ip_address);
	protected:
		comm_function();
	private:
		std::map<Route> route_table;
		std::string ip_address;
		int HELLO_INTERVAL;
		int SEQUENCE NUMBER;
		int ACTIVE_ROUTE_TIMEOUT;
		int PATH_DISCOVERY_TIME;

		void send_hello();
		void send_rreq();
		void send_rrep();
		void send_rerr();
}

//all of this is pending the helper classes for AODV messages
