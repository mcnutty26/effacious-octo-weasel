CXX			= g++
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -fPIC -g

SIMLINK		= -L ../liboctodrone/lib -I ../liboctodrone/include
PARLINK		= -L ../liboctodroneparrot/lib -I ../liboctodroneparrot/include
COMLINK		= -l ../liboctodronecomms/lib -I ../liboctodronecomms/include

SIMFLAGS	= -loctodrone
PARFLAGS	= -loctodroneparrot
COMFLAGS	= -loctodronecomms

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: BasicTest BasicAddrTest AodvTest ParrotTest Sensing

BasicTest:
	cp src/BasicTest/*.hpp include/
	$(CXX) $(CXXFLAGS) $(SIMLINK) $(COMLINK) $(SIMFLAGS) $(COMFLAGS) -c -o build/BasicTest.o src/BasicTest/BasicTest.cpp

BasicAddrTest:
	cp src/BasicAddrTest/*.hpp include/
	$(CXX) $(CXXFLAGS) $(SIMLINK) $(COMLINK) $(SIMFLAGS) $(COMFLAGS) -c -o build/AddrBasicTest.o src/BasicAddrTest/BasicAddrTest.cpp

AodvTest:
	cp src/AodvTest/*.hpp include/
	$(CXX) $(CXXFLAGS) $(SIMLINK) $(COMLINK) $(SIMFLAGS) $(COMFLAGS) -c -o build/AodvTest.o src/AodvTest/AodvTest.cpp

ParrotTest:
	cp src/ParrotTest/*.hpp include/
	$(CXX) $(CXXFLAGS) $(PARLINK) $(COMLINK) $(PARFLAGS) $(COMFLAGS) -c -o build/ParrotTest.o src/ParrotTest/ParrotTest.cpp

Sensing:
	cp src/Sensing/*.hpp include/
	$(CXX) $(CXXFLAGS) $(SIMLINK) $(COMLINK) $(SIMFLAGS) $(COMFLAGS) -c -o build/SensingDrone.o src/Sensing/SensingDrone.cpp
	$(CXX) $(CXXFLAGS) $(SIMLINK) $(COMLINK) $(SIMFLAGS) $(COMFLAGS) -c -o build/SensingBaseStation.o src/Sensing/SensingBaseStation.cpp

clean:
	$(RM) build/*
	$(RM) include/*
