#ifndef EOW_COMM_MOD_HPP
	#define EOW_COMM_MOD_HPP

	#include <string>
	#include <queue>
	#include "Mesage.hpp"

	class CommMod
	{
		public:
			CommMod(Environment* env, std::string ip_addr);
			void broadcast(Message message, double xPos, double yPos, double zPos, double range);
			void push_out_message(Message message);
			void push_in_message(Message message);
		protected:
			virtual void comm_function() = 0;
			std::queue<Message> outQueue;
			std::queue<Message> inQueue;
			Environment* environment;
			std::string ip_address;
	};

#endif
