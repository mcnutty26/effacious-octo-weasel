CXX		= g++
LINKFLAGS	=
CXXFLAGS	= -std=c++1y -Werror -Wall -Wextra -pthread
objects		= header Messageable Message CommMod  BaseStation Environment Drone
libraries	= -lglfw3 -lglew32 -lgdi32 -lopengl32
headers		= Messageable.hpp CommMod.hpp Message.hpp BaseStation.hpp Drone.hpp
exe		= 

all:$(objects)
	@echo "Objects successfully compiled"

header:
	@echo "Compiling simulator objects..."

Messageable: Messageable.cpp Messageable.hpp CommMod.hpp
	$(CXX) -c -o ../build/Messageable.o Messageable.cpp $(CXXFLAGS)

Message: Message.cpp Message.hpp
	$(CXX) -c -o ../build/Message.o Message.cpp $(CXXFLAGS)

CommMod: CommMod.cpp CommMod.hpp Message.hpp Environment.hpp
	$(CXX) -c -o ../build/CommMod.o CommMod.cpp $(CXXFLAGS)

BaseStation: BaseStation.cpp BaseStation.hpp CommMod.hpp Messageable.hpp
	$(CXX) -c -o ../build/BaseStation.o BaseStation.cpp $(CXXFLAGS)

Drone: Drone.cpp Drone.hpp CommMod.hpp Messageable.hpp
	$(CXX) -c -o ../build/Drone.o Drone.cpp $(CXXFLAGS)

Environment: Environment.cpp Environment.hpp BaseStation.hpp Drone.hpp
	$(CXX) -c -o ../build/Environment.o Environment.cpp $(CXXFLAGS)

clean:
	$(RM) ../build/*.o
