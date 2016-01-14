#ifndef EOW_COMM_MOD_HPP
	#define EOW_COMM_MOD_HPP

	#include <string>
	#include <queue>

	class CommMod
	{
		public:
			CommMod(Environment* env, std::string ip_addr);
			void broadcast(std::string message, double xPos, double yPos, double zPos, double range);
			void push_out_message(std::string message);
			void push_in_message(std::string message);
		protected:
			virtual void comm_function() = 0;
			std::queue<std::string> outQueue;
			std::queue<std::string> inQueue;
			Environment* environment;
      std::string ip_address;
	};

#endif
