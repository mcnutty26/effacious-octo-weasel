#ifndef EOW_MESSAGEABLE_HPP
	#define EOW_MESSAGEABLE_HPP

	#include <functional>
	#include <string>
	#include <queue>

	#include "CommMod.hpp"

	class Messageable
	{
		public:
			Messageable(CommMod cm);
			void send_message(std::string contents);
			std::string wait_for_message();
			void push_message(std::string contents);
			
			//returns true if the message is consumed by the callback.
			//false otherwise.
			virtual bool message_callback(std::string) = 0;
		protected:
			std::queue<std::string> inQueue;
			CommMod communicationsModule;
			std::function<void(std::string)> messageFun;
	};

#endif
