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

#ifndef EOW_BASE_STATION_HPP
	#define EOW_BASE_STATION_HPP

	#include "Messageable.hpp"
	class CommMod;

	class BaseStation : public Messageable{
		public:
			BaseStation(CommMod* cm, double xp, double yp, double zp);
	};

#endif
