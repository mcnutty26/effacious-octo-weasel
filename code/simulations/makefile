CXX		= g++
CXXFLAGS	= -std=c++11 -Wall -Wextra -fPIC -g
LDFLAGS		= -loctodronecomms -loctodrone -lpthread

COMLINK		= -L ../liboctodronecomms/lib -I ../liboctodronecomms/include
PRGLINK		= -I ../programs/include
SIMLINK		= -L ../liboctodrone/lib -I ../liboctodrone/include $(COMLINK) $(PRGLINK)
PARLINK		= -L ../liboctodroneparrot/lib -I ../liboctodroneparrot/include -loctodroneparrot $(COMLINK) $(PROGLINK)

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

vpath %.cpp src
vpath %.o ../programs/build

all: exes

exes: aodvtest

aodvtest: AodvTestSim.cpp AodvTest.o
	$(CXX) $(CXXFLAGS) $(SIMLINK) -o build/aodvtestsim src/AodvTestSim.cpp ../programs/build/AodvTest.o $(LDFLAGS)

clean:
	$(RM) build/*
