#ifndef EOW_ENVIRONMENT_HPP
	#define EOW_ENVIRONMENT_HPP

	#include <vector>
	#include <tuple>
	#include <map>
	#include <string>

	class BaseStation;
	class Drone;
	class Messageable;

	#include "Messageable.hpp"

	class Environment
	{
		typedef std::vector<std::vector<std::vector<double>>> data_type;

		public:
			void broadcast(std::string message, double xOrigin, double yOrigin, double zOrigin, double range);
			void addData(std::string type, data_type d);
			void addMessageable(Messageable* m);

			//should be called once and only once (per run)
			void run();

		private:
			BaseStation * baseStation;
			std::vector<Messageable*> messageables;
			std::map<std::string, data_type> data;
	};

#endif
