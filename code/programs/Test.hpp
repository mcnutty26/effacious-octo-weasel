#ifndef EOW_PROGRAMS_BASIC
	#define EOW_PROGRAMS_BASIC

	#include <string>
	#include <Drone.hpp>
	#include <CommMod.hpp>
	#include <Message.hpp>

	class Test: public Drone {
		public:
			Test(CommMod*, double, double, double, double, Environment*, bool);
			bool message_callback(Message*);
			void run();
		private:
			bool sink_node;

	};
#endif
