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

#ifndef EOW_BASIC_ADDRESSED
	#define EOW_BASIC_ADDRESSED

	#include <string>
	#include <Environment.hpp>
	#include <CommMod.hpp>
	#include <atomic>

	class Basic_addressed: public CommMod {
		public:
			Basic_addressed(Environment*, std::atomic_flag*, std::string ip);
			void log(std::string);
			std::string get_ip_address();

		protected:
			void comm_function();
		private:
			///The amount of power used to boradcast messages
			double RANGE;
			///An atomic lock to regulate access to stdout
			std::atomic_flag* lock;
			///The IP address of the communication module
			std::string ip_address;
			std::string get_attribute(std::string);
	};
#endif
