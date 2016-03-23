CXX		= g++
CXXFLAGS	= -std=c++11 -Wall -Wextra -fPIC -g

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: lib

parrot:
	$(call colorecho,"Compiling parrot objects...")
	$(CXX) $(CXXFLAGS) -c src/BaseStation.cpp -o build/BaseStation.o
	$(CXX) $(CXXFLAGS) -c src/CommMod.cpp -o build/CommMod.o
	$(CXX) $(CXXFLAGS) -c src/Drone.cpp -o build/Drone.o
	$(CXX) $(CXXFLAGS) -c src/Environment.cpp -o build/Environment.o
	$(CXX) $(CXXFLAGS) -c src/Message.cpp -o build/Message.o
	$(CXX) $(CXXFLAGS) -c src/Messageable.cpp -o build/Messageable.o
	$(CXX) $(CXXFLAGS) -c src/IpAllocator.cpp -o build/IpAllocator.o

lib: parrot
	$(call colorecho,"Creating parrot library...")
	cp src/*.hpp include/
	$(CXX) -shared -fPIC -o lib/liboctodroneparrot.so build/*.o

clean:
	$(call colorecho,"Cleaning parrot library...")
	$(RM) build/* 
	$(RM) lib/*
	$(RM) include/*
