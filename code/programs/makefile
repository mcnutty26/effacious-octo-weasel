CXX			= g++
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -fPIC -g

SIMLINK		= -L ../liboctodrone/lib -I ../liboctodrone/include
PARLINK		= -L ../liboctodroneparrot/lib -I ../liboctodroneparrot/include
COMLINK		= -L ../liboctodronecomms/lib -I ../liboctodronecomms/include

LDSIM		= -loctodrone -loctodronecomms
LDPAR		= -loctodroneparrot -loctodronecomms

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: BasicTest BasicAddrTest AodvTest ParrotTest Sensing

BasicTest:
	$(CXX) $(CXXFLAGS) $(SIMLINK) $(COMLINK) -I include -c -o build/BasicTest.o src/BasicTest/BasicTest.cpp $(LDSIM)

BasicAddrTest:
	$(CXX) $(CXXFLAGS) $(SIMLINK) $(COMLINK) -I include -c -o build/AddrBasicTest.o src/BasicAddrTest/BasicAddrTest.cpp $(LDSIM)

AodvTest:
	$(CXX) $(CXXFLAGS) $(SIMLINK) $(COMLINK) -I include -c -o build/AodvTest.o src/AodvTest/AodvTest.cpp $(LDSIM)

ParrotTest:
	$(CXX) $(CXXFLAGS) $(PARLINK) $(COMLINK) -I include -c -o build/ParrotTest.o src/ParrotTest/ParrotTest.cpp $(LDPAR)

Sensing:
	$(CXX) $(CXXFLAGS) $(SIMLINK) $(COMLINK) -I include -c -o build/SensingDrone.o src/Sensing/SensingDrone.cpp $(LDSIM)
	$(CXX) $(CXXFLAGS) $(SIMLINK) $(COMLINK) -I include -c -o build/SensingBaseStation.o src/Sensing/SensingBaseStation.cpp $(LDSIM)

clean:
	$(RM) build/*
