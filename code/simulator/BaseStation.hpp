#ifndef EOW_BASE_STATION_HPP
	#define EOW_BASE_STATION_HPP

	#include <string>

	#include "Messageable.hpp"
	#include "CommMod.hpp"

	class BaseStation
	:protected Messageable
	{
		public:
			BaseStation(CommMod* cm, double xp, double yp, double zp, std::string ip_addr)
			virtual void BaseStationFunction() = 0;
	};

#endif
