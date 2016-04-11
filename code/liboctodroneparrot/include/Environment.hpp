/*
This file is part of octoDrone.

octoDrone is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

octoDrone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with octoDrone.  If not, see <http://www.gnu.org/licenses/>.
*/

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
			Environment(std::map<std::string, data_type>, std::function<std::string(std::string)>, double timestep, std::string);
			Environment(std::map<std::string, data_type>, double timestep, std::string);
			void broadcast(std::string message, double xOrigin, double yOrigin, double zOrigin, double range, CommMod*);
			void addData(std::string type, data_type d);
			void addDrone(Drone* m);
			void setBaseStation(BaseStation* m);
			double getData(std::string type, double x, double y, double z);
			Drone* getDrone();
			double getTime();

			//should be called once and only once (per run)
			void run();

		private:
			double timeElapsed;
			double timeStep;
			std::string if_addr;

			BaseStation * baseStation;
			std::vector<Drone*> drones;
			std::map<std::string, data_type> data;
			std::function<std::string(std::string)> noiseFun;
	};

#endif
