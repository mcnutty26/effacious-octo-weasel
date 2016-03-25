#ifndef EOW_PROGRAMS_PARROT
	#define EOW_PROGRAMS_PARROT

	#include <string>
	#include <Drone.hpp>
	#include <CommMod.hpp>
	#include <Message.hpp>

	typedef std::vector<std::vector<std::vector<double>>> data_type;

	class ParrotTest: public Drone {
		public:
			ParrotTest(CommMod*, double, double, double, double, Environment*);
			bool message_callback(Message*);
			void run();
	};
#endif
