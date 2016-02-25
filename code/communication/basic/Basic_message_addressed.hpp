#ifndef EOW_BASIC_MESSAGE_ADDRESSED
	#define EOW_BASIC_MESSAGE_ADDRESSED

	#include <string>
	#include "Basic_message.hpp"
	#include <Message.hpp>

	class Basic_message_addressed: public Basic_message {
		public:
			Basic_message_addressed(std::string, std::string);
			Basic_message_addressed(std::string, std::string, std::string);
			std::string to_string();
			std::string get_message();
			std::string get_destination();
		private:
			std::string message;
			std::string destination;
	};
#endif
