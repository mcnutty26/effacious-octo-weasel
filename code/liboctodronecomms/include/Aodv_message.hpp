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

#ifndef EOW_AODV_MESSAGE
	#define EOW_AODV_MESSAGE

	#include <string>
	#include <Message.hpp>

	class Aodv_message: public Message{
		public:
			Aodv_message(std::string, int, int);
			std::string get_dest_ip();
			std::string serialize();
			int get_dest_seq();
			int get_ttl();
		private:
			///The IP address of the detination node
			std::string dest_ip;
			///The sequence number of the destination node
			int dest_seq;
			///The time to live of the message
			int ttl;
	};
#endif
