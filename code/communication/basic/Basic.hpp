#ifndef EOW_BASIC
	#define EOW_BASIC

	#include <string>
	#include <Environment.hpp>
	#include <CommMod.hpp>

	class Basic: public CommMod {
		public:
			Basic(Environment* env);
		protected:
			void comm_function();
		private:
			double RANGE;
			Environment* environment;
	};
#endif
