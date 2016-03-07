#ifndef EOW_BASIC_ADDRESSED
	#define EOW_BASIC_ADDRESSED

	#include <string>
	#include <Environment.hpp>
	#include <CommMod.hpp>
	#include <atomic>

	class Basic_addressed: public CommMod {
		public:
			Basic_addressed(Environment*, std::atomic_flag*, std::string ip);
		protected:
			void comm_function();
		private:
			double RANGE;
			Environment* environment;
			std::atomic_flag* lock;
			void log(std::string);
			std::string ip_address;
			std::string get_attribute(std::string);
	};
#endif
