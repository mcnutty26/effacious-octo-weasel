CXX			= g++
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -fPIC -g

COMLINK		= -I ../liboctodronecomms/include
SIMLINK		= -I ../liboctodrone/include $(COMLINK)
PARLINK		= -I ../liboctodroneparrot/include $(COMLINK)

vpath %.cpp	src
vpath %.hpp	include
vpath %.o	build

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: BasicTest.o BasicAddrTest.o AodvTest.o ParrotTest.o SensingDrone.o SensingBaseStation.o

BasicTest.o: BasicTest.cpp BasicTest.hpp
	$(CXX) $(CXXFLAGS) $(SIMLINK) -I include -c -o build/BasicTest.o src/BasicTest/BasicTest.cpp

BasicAddrTest:
	$(CXX) $(CXXFLAGS) $(SIMLINK) -I include -c -o build/AddrBasicTest.o src/BasicAddrTest/BasicAddrTest.cpp

AodvTest:
	$(CXX) $(CXXFLAGS) $(SIMLINK) -I include -c -o build/AodvTest.o src/AodvTest/AodvTest.cpp

ParrotTest:
	$(CXX) $(CXXFLAGS) $(PARLINK) -I include -c -o build/ParrotTest.o src/ParrotTest/ParrotTest.cpp

Sensing:
	$(CXX) $(CXXFLAGS) $(SIMLINK) -I include -c -o build/SensingDrone.o src/Sensing/SensingDrone.cpp
	$(CXX) $(CXXFLAGS) $(SIMLINK) -I include -c -o build/SensingBaseStation.o src/Sensing/SensingBaseStation.cpp

clean:
	$(RM) build/*
