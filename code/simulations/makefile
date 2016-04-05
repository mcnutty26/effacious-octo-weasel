CXX		= g++
CXXFLAGS	= -std=c++11 -Wall -Wextra -g
LDFLAGS		= -loctodronecomms -loctodrone -lpthread

COMLINK		= -L ../liboctodronecomms/lib -I ../liboctodronecomms/include
PRGLINK		= ../programs/build/*.o -I ../programs/include
SIMLINK		= $(PRGLINK) $(COMLINK) -L ../liboctodrone/lib -I ../liboctodrone/include
PARLINK		= $(PRGLINK) $(COMLINK) -L ../liboctodroneparrot/lib/ -I ../liboctodroneparrot/include

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

vpath %.cpp src
vpath %.o build

all: aodvtest basictest parrottest sensing

AodvTestSim.o: AodvTestSim.cpp
	$(CXX) $(CXXFLAGS) -c -o build/AodvTestSim.o src/AodvTestSim.cpp $(SIMLINK)

BasicTestSim.o: BasicTestSim.cpp
	$(CXX) $(CXXFLAGS) -c -o build/BasicTestSim.o src/BasicTestSim.cpp -I ../liboctodrone/include -I ../liboctodronecomms/include -I ../programs/include

ParrotTestSim.o: ParrotTestSim.cpp
	$(CXX) $(CXXFLAGS) -c -o build/ParrotTestSim.o src/ParrotTestSim.cpp -I ../liboctodrone/include -I ../liboctodronecomms/include -I ../programs/include

SensingSim.o: SensingSim.cpp
	$(CXX) $(CXXFLAGS) -c -o build/SensingSim.o src/SensingSim.cpp -I ../liboctodrone/include -I ../liboctodronecomms/include -I ../programs/include

aodvtest: AodvTestSim.o
	$(CXX) $(CXXFLAGS) -o bin/aodvtestsim build/AodvTestSim.o ../liboctodronecomms/src/Basic_message.cpp $(SIMLINK) $(LDFLAGS)

basictest: BasicTestSim.o
	$(CXX) $(CXXFLAGS) -o bin/basictestsim build/BasicTestSim.o ../liboctodronecomms/src/Basic_message.cpp $(SIMLINK) $(LDFLAGS)

parrottest: ParrotTestSim.o
	$(CXX) $(CXXFLAGS) -o bin/parrottestsim build/ParrotTestSim.o ../liboctodronecomms/src/Basic_message.cpp $(SIMLINK) $(LDFLAGS)

sensing: SensingSim.o
	$(CXX) $(CXXFLAGS) -o bin/sensingsim build/SensingSim.o ../liboctodronecomms/src/Basic_message.cpp $(SIMLINK) $(LDFLAGS)

clean:
	$(RM) build/*
