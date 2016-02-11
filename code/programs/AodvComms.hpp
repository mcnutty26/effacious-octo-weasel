#ifndef EOW_PROGRAMS_AODVCOMMS
	#define EOW_PROGRAMS_AODVCOMMS

	#include <string>
	#include <Drone.hpp>
	#include <CommMod.hpp>
	#include <Message.hpp>

	typedef std::vector<std::vector<std::vector<double>>> data_type;

	class AodvComms: public Drone {
		public:
			AodvComms(CommMod*, double, double, double, double, Environment*, bool);
			bool message_callback(Message*);
			void run();
		private:
			bool sink_node;

	};
#endif
