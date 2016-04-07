#ifndef LIB_OCTO_DRONE_HPP
	#define LIB_OCTO_DRONE_HPP

	#include <vector>

	enum class IMG
	{
		DRONE,
		STATION,
		BCAST
	};

	class Element
	{
		public:
			Element(IMG img, int x, int y, int size, int steps);
			void draw();
			bool step();
		private:
			int stepsLeft;
			int x, y;
			int size;
			IMG image;
	};

	std::vector<Element> elements;

	void pushDrone(int x, int y);
	void pushBcast(int x, int y, int range);
	void pushBstation(int x, int y);
	void step();
	void visLoop();
	void visKill();

#endif
