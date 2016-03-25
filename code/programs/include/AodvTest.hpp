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
