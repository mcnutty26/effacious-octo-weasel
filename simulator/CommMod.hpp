#ifndef EOW_COMM_MOD_HPP
	#define EOW_COMM_MOD_HPP

	#include <functional>
	#include <string>
	#include <queue>

	class CommMod
	{
		public:
			void broadcast(std::string message);
			void push_out_message(std::string message);
			void push_in_message(std::string message);
		protected:
			virtual void comm_function() = 0;
			std::queue<std::string> outQueue;
			std::queue<std::string> inQueue;
	};

#endif
