CXX		= g++
LINKFLAGS	= -L ../simulator/build -I ../simulator -L ../communication/build
BASICLINK	= -I ../communication/basic
BASICADDRLINK	= -I ../communication/basic_addressed $(BASICLINK)
AODVLINK	= -I ../communication/aodv $(BASICADDRLINK)
LIBFLAGS	= -loctodrone -loctodronecomms -lpthread
CXXFLAGS	= -std=c++11 -Werror -Wextra -g

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: complete

deps:
	cd ../simulator && $(MAKE)
	cp ../simulator/build/liboctodrone.so build/
	cd ../communication && $(MAKE)
	cp ../communication/build/liboctodronecomms.so build/

programs: 
	$(call colorecho,"Compiling drone routines...")
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) $(LINKFLAGS) $(BASICLINK) -c -o build/BasicComms.o BasicComms.cpp
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) $(LINKFLAGS) $(AODVLINK) -c -o build/AodvComms.o AodvComms.cpp
	#$(CXX) $(CXXFLAGS) $(LIBFLAGS) $(LINKFLAGS) $(BASICADDRLINK) -c -o build/SensingDrone.o SensingDrone.cpp

exes:
	$(call colorecho,"Creating executables...")
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(LIBFLAGS) $(BASICLINK) -I ../ -o build/basiccomms BasicComms_exe.cpp build/BasicComms.o
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(LIBFLAGS) $(AODVLINK) -I ../ -o build/aodvcomms AodvComms_exe.cpp build/AodvComms.o

complete: deps programs exes

clean:
	$(RM) build/*
	cd ../simulator && $(MAKE) clean
	cd ../communication && $(MAKE) clean
