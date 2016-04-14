CXX		= g++
CXXFLAGS	= -std=c++11 -Wall -Wextra -Werror -I include

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

vpath %.cpp src
vpath %.o build
vpath %.hpp include

all: lib

parrot: BaseStation.o CommMod.o Drone.o Environment.o Message.o IpAllocator.o Messageable.o
	$(call colorecho,"Compiling parrot objects...")

BaseStation.o: BaseStation.cpp BaseStation.hpp
	$(CXX) $(CXXFLAGS) -c src/BaseStation.cpp -o build/BaseStation.o

CommMod.o: CommMod.cpp CommMod.hpp
	$(CXX) $(CXXFLAGS) -c src/CommMod.cpp -o build/CommMod.o

Drone.o: Drone.cpp Drone.hpp
	$(CXX) $(CXXFLAGS) -c src/Drone.cpp -o build/Drone.o

Environment.o: Environment.cpp Environment.hpp
	$(CXX) $(CXXFLAGS) -c src/Environment.cpp -o build/Environment.o

Message.o: Message.cpp Message.hpp
	$(CXX) $(CXXFLAGS) -c src/Message.cpp -o build/Message.o

Messageable.o: Messageable.cpp Messageable.hpp
	$(CXX) $(CXXFLAGS) -c src/Messageable.cpp -o build/Messageable.o

IpAllocator.o: IpAllocator.cpp IpAllocator.hpp 
	$(CXX) $(CXXFLAGS) -c src/IpAllocator.cpp -o build/IpAllocator.o

lib: parrot
	$(call colorecho,"Creating parrot library...")
	ar rvs lib/liboctodroneparrot.a build/*.o

clean:
	$(call colorecho,"Cleaning parrot library...")
	$(RM) build/* 
	$(RM) lib/*
