#ifndef EOW_BASE_STATION_HPP
	#define EOW_BASE_STATION_HPP

	#include "Messageable.hpp"
	class CommMod;

	class BaseStation : public Messageable{
		public:
			BaseStation(CommMod*, double, double, double);
	};

#endif
