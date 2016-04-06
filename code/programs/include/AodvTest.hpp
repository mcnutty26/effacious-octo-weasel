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

#ifndef EOW_PROGRAMS_AODV
	#define EOW_PROGRAMS_AODV

	#include <string>
	#include <Drone.hpp>
	#include <CommMod.hpp>
	#include <Message.hpp>
	#include <atomic>

	typedef std::vector<std::vector<std::vector<double>>> data_type;

	class AodvTest: public Drone {
		public:
			AodvTest(CommMod*, double, double, double, double, Environment*, int, int*, std::atomic_flag*);
			bool message_callback(Message*);
			void run();
		private:
			int m_task;
			int* m_flag;
			std::atomic_flag* m_lock;
			Environment* m_env;
	};
#endif
