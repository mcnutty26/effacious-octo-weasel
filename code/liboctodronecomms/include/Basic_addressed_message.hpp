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

#ifndef EOW_BASIC_addressed_message
	#define EOW_BASIC_addressed_message

	#include <string>
	#include "Basic_message.hpp"

	class Basic_addressed_message: public Basic_message {
		public:
			Basic_addressed_message(std::string, std::string, std::string);
			std::string to_string();
			std::string get_message();
			std::string get_destination();
			std::string get_source();
		private:
			///The contents of the message
			std::string message;
			///The IP address of the messages destination
			std::string destination;
			///The IP address of the node which sent the message
			std::string source;
	};
#endif
