#ifndef EOW_BASE_STATION_HPP
	#define EOW_BASE_STATION_HPP

	#include "Messageable.hpp"
	class CommMod;

	class BaseStation : public Messageable{
		public:
			BaseStation(CommMod* cm, double xp, double yp, double zp, double areaX1, double areaY1, double areaX2, double areaY2);
	};

#endif
