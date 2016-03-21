/*
This file is part of TBC.

TBC is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

TBC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with TBC.  If not, see <http://www.gnu.org/licenses/>.
*/

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
	#include <atomic>

	class Aodv: public CommMod {
		public:
			Aodv(Environment*, std::string, std::atomic_flag*, bool);
		protected:
			void comm_function();
		private:
			///Routing table for the communication module
			std::map<std::string, Aodv_route*> route_table;
			///The IP address of the communication module
			std::string ip_address;
			///The interval at which hello messages are sent to discover nearby nodes
			double HELLO_INTERVAL;
			///The AODV sequence number of the communication module
			int SEQUENCE_NUMBER;
			///The AODV active route timeout used to determine how long routes stay fresh for
			double ACTIVE_ROUTE_TIMEOUT;
			///How long to wait for relies to route requests
			double PATH_DISCOVERY_TIME;
			///AODV broadcast ID used to prevent loops and ensure fresh information
			int BROADCAST_ID;
			///The amount of power used to boradcast messages
			int RANGE;
			///Default time to live for messages, dependent on network size
			int TTL;
			///The time at which the last hello message was sent
			double last_hello;

			Aodv_rreq* create_hello();
			Aodv_rreq* create_rreq(std::string, std::string, int);
			Aodv_rrep* create_rrep(std::string, std::string, int);
			Aodv_rerr* create_rerr(std::string, int);

			void process_rreq(Aodv_rreq*);
			void process_rrep(Aodv_rrep*);
			void process_rerr(Aodv_rerr*);
			void process_data(std::string);

			std::string get_attribute(std::string);
			bool have_route(std::string);
			void add_route(std::string, int, int, std::string);

			Aodv_rreq* deserialize_rreq(std::string);
			Aodv_rrep* deserialize_rrep(std::string);
			Aodv_rerr* deserialize_rerr(std::string);

			std::pair<std::string, std::string> current_message;
			///The internal state of the AODV implementation
			int state;
			///An atomic lock to regulate access to stdout
			std::atomic_flag* lock;
			void log(std::string);
			void broadcast(std::string);
			///Switch to enable or disable logging
			bool logging;
	};
#endif
