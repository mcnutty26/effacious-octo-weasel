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

			double areaX1;
			double areaX2;
			double areaY1;
			double areaY2;

	};
#endif
