#ifndef EOW_ENVIRONMENT_HPP
	#define EOW_ENVIRONMENT_HPP

	#include <vector>
	#include <tuple>
	#include <map>
	#include <string>
	#include <functional>

	class Messageable;
	class Drone;
	class BaseStation;
	class CommMod;

	class Environment
	{
		typedef std::vector<std::vector<std::vector<double>>> data_type;

		public:
			Environment(std::map<std::string, data_type>, std::function<std::string(std::string)>, double timestep);
			Environment(std::map<std::string, data_type>, int timestep);
			void broadcast(std::string message, double xOrigin, double yOrigin, double zOrigin, double range, CommMod*);
			void addData(std::string type, data_type d);
			void addDrone(Drone* m);
			void setBaseStation(BaseStation* m);
			double getData(std::string type, double x, double y, double z);

			double getTime();

			//should be called once and only once (per run)
			void run();

		private:
			double timeElapsed
			double timeStep;

			BaseStation * baseStation;
			std::vector<Drone*> drones;
			std::map<std::string, data_type> data;
			std::function<std::string(std::string)> noiseFun;
	};

#endif
