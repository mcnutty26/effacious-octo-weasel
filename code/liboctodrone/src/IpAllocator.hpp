#ifndef EOW_IPALLOCATOR
	#define EOW_IPALLOCATOR

	#include <string>

	class IpAllocator{
		public:
			IpAllocator(int, int, int, int);
			std::string next();

		private:
			int m_first;
			int m_second;
			int m_third;
			int m_fourth;
	};

#endif
