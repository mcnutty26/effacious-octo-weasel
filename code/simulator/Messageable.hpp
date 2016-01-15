#ifndef EOW_MESSAGEABLE_HPP
	#define EOW_MESSAGEABLE_HPP

	#include <functional>
	#include <string>
	#include <queue>

	#include "CommMod.hpp"
	#include "Message.hpp"

	class Messageable
	{
		public:
			Messageable(CommMod* cm, double xp, yp, zp, std::string ip_addr);
			void send_message(Message contents);
			Message wait_for_message();
			void push_message(std::string contents);
			void receive_message(std::string contents);

			double getX();
			double getY();
			double getZ();
			
			//returns true if the message is consumed by the callback.
			//false otherwise.
			virtual bool message_callback(Message) = 0;
		protected:
			std::queue<std::string> inQueue;
			CommMod* communicationsModule;
			std::function<void(std::string)> messageFun;
			double xPos;
			double yPos;
			double zPos;
			std::string ip_address;
	};

#endif
