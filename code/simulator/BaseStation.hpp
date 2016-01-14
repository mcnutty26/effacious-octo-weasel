#ifndef EOW_BASE_STATION_HPP
	#define EOW_BASE_STATION_HPP

	#include <functional>
	#include <string>

	#include "CommMod.hpp"

	class BaseStation
	{
		public:
			BaseStation(std::function<void(std::string)> fun, CommMod cm);
			void run();
			void send_message(std::string contents);
			std::string wait_for_message();
			void message_callback(std::function<void()>)
		private:
			std::function<void(std::string)> bs_fun;
			CommMod communicationsModule;
	};

#endif
