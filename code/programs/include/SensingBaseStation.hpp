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

#ifndef EOW_PROGRAMS_SENSINGBASESTATION
	#define EOW_PROGRAMS_SENSINGBASESTATION

	#include <string>
	#include <BaseStation.hpp>
	#include <CommMod.hpp>
	#include <Message.hpp>

	class SensingBaseStation: public BaseStation {
		public:
			SensingBaseStation(CommMod* cm, double xp, double yp, double zp, double areaX1, double areaY1, double areaX2, double areaY2);

			void run();

			bool message_callback(Message* message);

		private:

			std::vector<std::string> droneIPs;

			void interpretMessage(Message* message);

			void log(std::string);

			double areaX1;
			double areaX2;
			double areaY1;
			double areaY2;

	};
#endif
