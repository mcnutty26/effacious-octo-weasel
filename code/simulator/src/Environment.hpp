#ifndef EOW_ENVIRONMENT_HPP
	#define EOW_ENVIRONMENT_HPP

	#include <vector>
	#include <tuple>
	#include <map>
	#include <string>
	#include <functional>

	class BaseStation;
	class Drone;
	class Messageable;

	#include "Messageable.hpp"

	class Environment
	{
		typedef std::vector<std::vector<std::vector<double>>> data_type;

		public:
			Environment();
			Environment(std::function<std::string(std::string)> nFun);
			void broadcast(std::string message, double xOrigin, double yOrigin, double zOrigin, double range);
			void addData(std::string type, data_type d);
			void addMessageable(Messageable* m);
			double getData(std::string type, double x, double y, double z);

			//should be called once and only once (per run)
			void run();

		private:
			BaseStation * baseStation;
			std::vector<Messageable*> messageables;
			std::map<std::string, data_type> data;
			std::function<std::string(std::string)> noiseFun;
	};

#endif
