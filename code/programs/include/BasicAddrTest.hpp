#ifndef EOW_PROGRAMS_BASIC_ADDR
	#define EOW_PROGRAMS_BASIC_ADDR

	#include <string>
	#include <Drone.hpp>
	#include <CommMod.hpp>
	#include <Message.hpp>

	typedef std::vector<std::vector<std::vector<double>>> data_type;

	class BasicAddrTest: public Drone {
		public:
			BasicAddrTest(CommMod*, double, double, double, double, Environment*, bool);
			bool message_callback(Message*);
			void run();
		private:
			bool sink_node;

	};
#endif
