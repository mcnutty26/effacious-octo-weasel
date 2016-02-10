#ifndef EOW_BASIC_MESSAGE
	#define EOW_BASIC_MESSAGE

	#include <string>
	#include "Basic_message.hpp"
	#include <Message.hpp>

	class Basic_message: public Message {
		public:
			Basic_message(std::string);
			std::string to_string();
		private:
			std::string message;
	};
#endif
