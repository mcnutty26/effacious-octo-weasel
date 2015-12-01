#ifndef EOW_DRONE_HPP
	#define EOW_DRONE_HPP

	#include <functional>
	#include <string>

	#include "CommMod.hpp"

	class Drone
	{
		public:
			Drone(std::function<void()> fun, CommMod cm);
			void run();
			void send_message(std::string contents);
			std::string wait_for_message();
			void message_callback(std::function<void()>)

			double xPos, yPos, zPos;
			double maxX, maxY, maxZ;
			double xAng, yAng, zAng;

		private:
			std::function<void()> droneFun;
			CommMod communicationsModule;
	};

#endif
