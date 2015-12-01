#ifndef EOW_ENVIRONMENT_HPP
	#define EOW_ENVIRONMENT_HPP

	#include <vector>
	#include <map>
	#include <string>

	#include "BaseStation.hpp"
	#include "Drone.hpp"

	class Environment
	{
		typedef std::vector<std::vector<std::vector<double>>> data_type;

		public:
			Environment(BaseStation bs);
			void addData(std::string name, data_type data);
			void addDrone(Drone d);

		private:
			BaseStation baseStation;
			std::vector<Drone> drones;
			std::map<std::string, data_type> data;
	};

#endif
