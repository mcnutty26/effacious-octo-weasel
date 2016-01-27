#ifndef EOW_AODV_MAIN
	#define EOW_AODV_MAIN

	#include <string>
	#include <map>
	#include <Environment.hpp>
	#include <CommMod.hpp>
	#include "Aodv_message.hpp"
	#include "Aodv_rreq.hpp"
	#include "Aodv_rrep.hpp"
	#include "Aodv_rerr.hpp"
	#include "Aodv_route.hpp"

	class Aodv: public CommMod {
		public:
			Aodv(Environment* env);
		protected:
			void comm_function();
		private:
			std::map<std::string, Aodv_route> route_table;
			std::string ip_address;
			int HELLO_INTERVAL;
			int SEQUENCE_NUMBER;
			int ACTIVE_ROUTE_TIMEOUT;
			int PATH_DISCOVERY_TIME;
			int BROADCAST_ID;

			void init();
			Aodv_rreq create_hello();
			Aodv_rreq create_rreq(std::string, int);
			Aodv_rrep create_rrep(std::string);
			Aodv_rerr create_rerr();

			std::string get_attribute(std::string);
			Aodv_rreq deserialize_rreq(std::string);
			Aodv_rrep deserialize_rrep(std::string);
			Aodv_rerr deserialize_rerr(std::string);
	};
#endif
