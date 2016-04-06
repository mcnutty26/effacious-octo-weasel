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
