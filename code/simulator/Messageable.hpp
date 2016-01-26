#ifndef EOW_MESSAGEABLE_HPP
	#define EOW_MESSAGEABLE_HPP

	#include <string>
	#include <queue>

	#include "CommMod.hpp"
	#include "Message.hpp"

	class CommMod;

	class Messageable
	{
		public:
			Messageable(CommMod* cm, double xp, double yp, double zp);
			void send_message(Message* contents);
			Message* wait_for_message();
			void push_message(Message* contents);
			void receive_message(std::string contents);

			double getX();
			double getY();
			double getZ();
			
			//returns true if the message is consumed by the callback.
			//false otherwise.
			virtual bool message_callback(Message* message) = 0;

			//should terminate when the task is finished.
			virtual void run() = 0;

			void runCommMod();
		protected:
			std::queue<Message*> inQueue;
			CommMod* communicationsModule;
			double xPos;
			double yPos;
			double zPos;
	};

#endif
