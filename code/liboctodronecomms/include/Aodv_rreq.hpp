/*
This file is part of octoDrone.

octoDrone is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

octoDrone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with octoDrone.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef EOW_AODV_RREQ
	#define EOW_AODV_RREQ

	#include <string>
	#include "Aodv_message.hpp"

	class Aodv_rreq: public Aodv_message {
		public:
			Aodv_rreq(int hop, std::string src_ip, std::string dst_ip, int src_seq, int dst_seq, int ttl);
			int get_hop_count();
			std::string get_source_ip();
			std::string to_string();
			int get_source_seq();
		private:
			///The number of hops taken towards the destination
			int hop_count;
			///The IP address of the sending node
			std::string source_ip;
			///The sequence number of the sending node
			int source_seq;
	};
#endif
