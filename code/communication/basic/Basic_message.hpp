#ifndef EOW_BASIC_MESSAGE
	#define EOW_BASIC_MESSAGE

	#include <string>
	#include <Message.hpp>

	class Basic_message: public Message {
		public:
			Basic_message(std::string);
			std::string to_string();
		private:
			///The contents of the message
			std::string message;
	};
#endif
