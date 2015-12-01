#ifndef EOW_COMM_MOD_HPP
	#define EOW_COMM_MOD_HPP

	#include <functional>
	#include <string>
	#include <queue>

	class CommMod
	{
		public:
			CommMod(std::function<void()> fun);
			broadcast(std::string message);
			std::queue<std::string> outQueue;
			std::queue<std::string> inQueue;
		private:
			std::function<void()> commFun;
	};

#endif
