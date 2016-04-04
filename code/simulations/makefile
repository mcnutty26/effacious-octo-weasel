CXX			= g++
CXXFLAGS	= -std=c++11 -Wall -Wextra -fPIC -g

SIMLINK		= -L ../liboctodrone/lib -I ../liboctodrone/include -loctodrone
PARLINK		= -L ../liboctodroneparrot/lib -I ../liboctodroneparrot/include -loctodroneparrot
COMLINK		= -L ../liboctodronecomms/lib -I ../liboctodronecomms/include -loctodronecomms
PRGLINK		= -I ../programs/include

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: exes

exes:
	$(CXX) $(CXXFLAGS) $(SIMLINK) $(COMLINK) $(PRGLINK) ../programs/build/AodvTest.o src/AodvTestSim.cpp -o build/AodvTestSim

clean:
	$(RM) build/*
