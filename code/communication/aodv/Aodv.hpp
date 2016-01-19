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

		Aodv_message deserialize(std::string);
		Aodv_message deserialize_message(std::string);
		Aodv_rreq deserialize_rreq(std::string);
		Aodv_rrep deserialize_rrep(std::string);
		Aodv_rerr deserialize_rerr(std::string);
}
