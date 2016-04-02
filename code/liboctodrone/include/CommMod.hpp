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

			///Main loop which must be defined by communications implementations
			virtual void comm_function() = 0;

			double getTime();
		protected:
			///the queue of messages to be sent
			std::queue<Message*> outQueue;
			
			///the queue of received messages waiting for collection by the messageable
			std::queue<std::string> inQueue;

			///Reference to the simulation environment
			Environment* environment;

			///Reference to the associated messageable
			Messageable* messageable;
	};

#endif
