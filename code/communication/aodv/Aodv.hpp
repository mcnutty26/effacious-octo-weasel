#include <string>

class Aodv: public CommMod {
	public:
		Aodv(Environment* env, String ip_address);
	protected:
		comm_function();
	private:
		std::string ip_address;
		final int HELLO_INTERVAL;
		final int SEQUENCE NUMBER;
		final int ACTIVE_ROUTE_TIMEOUT;
		final int PATH_DISCOVERY_TIME;

		send_hello();
		send_rreq();
		send_rrep();
		send_rerr();
}

//all of this is pending the helper classes for AODV messages