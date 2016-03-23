#ifndef EOW_BASIC
	#define EOW_BASIC

	#include <string>
	#include <Environment.hpp>
	#include <CommMod.hpp>
	#include <atomic>

	class Basic: public CommMod {
		public:
			Basic(Environment*, std::atomic_flag*);
		protected:
			void comm_function();
		private:
			///The amount of power used to broadcast messages
			double RANGE;
			///An atomic lock to regulate access to stdout
			std::atomic_flag* lock;
			void log(std::string);
	};
#endif
