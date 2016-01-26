CXX			= g++
LINKFLAGS   =
CXXFLAGS	= -std=c++1y -Werror -Wall -Wextra -pthread
objects		= Messageable.o Message.o CommMod.o BaseStation.o Environment.o
libraries	= -lglfw3 -lglew32 -lgdi32 -lopengl32
headers		= Messageable.hpp CommMod.hpp Message.hpp BaseStation.hpp Drone.hpp
exe			=

Objects:$(objects)

Messageable.o: Messageable.cpp Messageable.hpp CommMod.hpp
	$(CXX) -c -o Messageable.o Messageable.cpp $(CXXFLAGS)

Message.o: Message.cpp Message.hpp
	$(CXX) -c -o Message.o Message.cpp $(CXXFLAGS)

CommMod.o: CommMod.cpp CommMod.hpp Message.hpp Environment.hpp
	$(CXX) -c -o CommMod.o CommMod.cpp $(CXXFLAGS)

BaseStation.o: BaseStation.cpp BaseStation.hpp CommMod.hpp Messageable.hpp
	$(CXX) -c -o BaseStation.o BaseStation.cpp $(CXXFLAGS)

Drone.o: Drone.cpp Drone.hpp CommMod.hpp Messageable.hpp
	$(CXX) -c -o Drone.o Drone.cpp $(CXXFLAGS)

Environment.o: Environment.cpp Environment.hpp BaseStation.hpp Drone.hpp
	$(CXX) -c -o Environment.o Environment.cpp $(CXXFLAGS)
