CXX		= g++
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -g

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
	$(CXX) $(CXXFLAGS) $(SIMLINK) -I include -c -o build/BasicTest.o src/BasicTest.cpp

BasicAddrTest.o: BasicAddrTest.cpp BasicAddrTest.hpp
	$(CXX) $(CXXFLAGS) $(SIMLINK) -I include -c -o build/BasicAddrTest.o src/BasicAddrTest.cpp

AodvTest.o: AodvTest.cpp AodvTest.hpp
	$(CXX) $(CXXFLAGS) $(SIMLINK) -I include -c -o build/AodvTest.o src/AodvTest.cpp

ParrotTest.o: ParrotTest.cpp ParrotTest.hpp
	$(CXX) $(CXXFLAGS) $(PARLINK) -I include -c -o build/ParrotTest.o src/ParrotTest.cpp

SensingDrone.o: SensingDrone.cpp SensingDrone.hpp
	$(CXX) $(CXXFLAGS) $(SIMLINK) -I include -c -o build/SensingDrone.o src/SensingDrone.cpp

SensingBaseStation.o: SensingBaseStation.cpp SensingBaseStation.hpp
	$(CXX) $(CXXFLAGS) $(SIMLINK) -I include -c -o build/SensingBaseStation.o src/SensingBaseStation.cpp

clean:
	$(RM) build/*
