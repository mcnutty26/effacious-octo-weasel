CXX		= g++
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -fPIC -g -I include
LDFLAGS	= -lpthread

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: lib

simulator:
	$(call colorecho,"Compiling simulator objects...")
	$(CXX) $(CXXFLAGS) -c src/BaseStation.cpp 	-o build/BaseStation.o 	$(LDFLAGS)
	$(CXX) $(CXXFLAGS) -c src/CommMod.cpp 		-o build/CommMod.o 	$(LDFLAGS)
	$(CXX) $(CXXFLAGS) -c src/Drone.cpp 		-o build/Drone.o 	$(LDFLAGS)
	$(CXX) $(CXXFLAGS) -c src/Environment.cpp 	-o build/Environment.o 	$(LDFLAGS)
	$(CXX) $(CXXFLAGS) -c src/Message.cpp 		-o build/Message.o 	$(LDFLAGS)
	$(CXX) $(CXXFLAGS) -c src/Messageable.cpp 	-o build/Messageable.o 	$(LDFLAGS)
	$(CXX) $(CXXFLAGS) -c src/IpAllocator.cpp 	-o build/IpAllocator.o 	$(LDFLAGS)

lib: simulator
	$(call colorecho,"Creating simulator library...")
	$(CXX) -shared -fPIC -o lib/liboctodrone.so build/*.o

clean:
	$(call colorecho,"Cleaning simulator library...")
	$(RM) build/* 
	$(RM) lib/*
