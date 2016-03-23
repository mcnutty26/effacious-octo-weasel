#ifndef EOW_COMM_MOD_HPP
	#define EOW_COMM_MOD_HPP

	#include <string>
	#include <queue>
	#include "Message.hpp"
	#include "Environment.hpp"
	#include "Messageable.hpp"

	class Environment;

	class CommMod
	{
		public:
			CommMod(Environment* env);
			void set_messageable(Messageable* msg);
			void broadcast(std::string message, double xPos, double yPos, double zPos, double range);
			void broadcast(Message* message, double xPos, double yPos, double zPos, double range);
			void push_out_message(Message* message);
			void push_in_message(std::string message);
			virtual void comm_function() = 0;

			double getTime();
		protected:
			//the queue of outbound (sent) messages
			std::queue<Message*> outQueue;
			
			//the queue of inbound (recieved) messages
			std::queue<std::string> inQueue;

			Environment* environment;
			Messageable* messageable;
	};

#endif
