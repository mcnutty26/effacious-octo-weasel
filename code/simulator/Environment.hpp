#ifndef EOW_ENVIRONMENT_HPP
	#define EOW_ENVIRONMENT_HPP

	#include <vector>
	#include <tuple>
	#include <map>
	#include <string>

	#include "BaseStation.hpp"
	#include "Drone.hpp"

	class Environment
	{
		typedef std::vector<std::vector<std::vector<double>>> data_type;

		public:
			void broadcast(std::string message, double xOrigin, double yOrigin, double zOrigin, double range)
			void addData(std::string type, data_type d);
			void addMessageable(Messageable* m);

		private:
			BaseStation baseStation;
			std::vector<Messageable*> messageables;
			std::map<std::string, data_type> data;
	};

#endif
