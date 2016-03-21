#ifndef EOW_BASIC_MESSAGE_ADDRESSED
	#define EOW_BASIC_MESSAGE_ADDRESSED

	#include <string>
	#include "../basic/Basic_message.hpp"

	class Basic_message_addressed: public Basic_message {
		public:
			Basic_message_addressed(std::string, std::string, std::string);
			std::string to_string();
			std::string get_message();
			std::string get_destination();
			std::string get_source();
		private:
			///The contents of the message
			std::string message;
			///The IP address of the messages destination
			std::string destination;
			///The IP address of the node which sent the message
			std::string source;
	};
#endif
