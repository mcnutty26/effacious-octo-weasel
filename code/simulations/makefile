CXX		= g++
CXXFLAGS	= -std=c++11 -Wall -Wextra -Werror -g
SLDFLAGS	= -loctodronecomms -loctodrone -lpthread -lglfw3 -lGLEW -lGL -lX11 -lXrandr -lXi -lXxf86vm -ldl -lXext -lXinerama -lXcursor
PLDFLAGS	= -loctodronecomms -loctodroneparrot -lpthread

COMLINK		= -L ../liboctodronecomms/lib -I ../liboctodronecomms/include
PRGLINK		= ../programs/build/*.o -I ../programs/include
SIMLINK		= $(PRGLINK) $(COMLINK) -L ../liboctodrone/lib -I ../liboctodrone/include -L ./lib
PARLINK		= $(PRGLINK) $(COMLINK) -L ../liboctodroneparrot/lib/ -I ../liboctodroneparrot/include

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

vpath %.cpp src
vpath %.o build

all: aodvtest basictest parrottest sensing tod scale

AodvTestSim.o: AodvTestSim.cpp
	$(CXX) $(CXXFLAGS) -c -o build/AodvTestSim.o src/AodvTestSim.cpp -I ../liboctodrone/include -I ../liboctodronecomms/include -I ../programs/include

BasicTestSim.o: BasicTestSim.cpp
	$(CXX) $(CXXFLAGS) -c -o build/BasicTestSim.o src/BasicTestSim.cpp -I ../liboctodrone/include -I ../liboctodronecomms/include -I ../programs/include

Scale.o: Scale.cpp
	$(CXX) $(CXXFLAGS) -c -o build/Scale.o src/Scale.cpp -I ../liboctodrone/include -I ../liboctodronecomms/include -I ../programs/include

ParrotTestSimA.o: ParrotTestSimA.cpp
	$(CXX) $(CXXFLAGS) -c -o build/ParrotTestSimA.o src/ParrotTestSimA.cpp -I ../liboctodroneparrot/include -I ../liboctodronecomms/include -I ../programs/include

ParrotTestSimB.o: ParrotTestSimB.cpp
	$(CXX) $(CXXFLAGS) -c -o build/ParrotTestSimB.o src/ParrotTestSimB.cpp -I ../liboctodroneparrot/include -I ../liboctodronecomms/include -I ../programs/include

SensingSim.o: SensingSim.cpp
	$(CXX) $(CXXFLAGS) -c -o build/SensingSim.o src/SensingSim.cpp -I ../liboctodrone/include -I ../liboctodronecomms/include -I ../programs/include

toda.o: TODa.cpp
	$(CXX) $(CXXFLAGS) -c -o build/toda.o src/TODa.cpp -I ../liboctodroneparrot/include -I ../liboctodronecomms/include -I ../programs/include

todb.o: TODb.cpp
	$(CXX) $(CXXFLAGS) -c -o build/todb.o src/TODb.cpp -I ../liboctodroneparrot/include -I ../liboctodronecomms/include -I ../programs/include

cada.o: CADa.cpp
	$(CXX) $(CXXFLAGS) -c -o build/cada.o src/CADa.cpp -I ../liboctodroneparrot/include -I ../liboctodronecomms/include -I ../programs/include

cada.o: CADb.cpp
	$(CXX) $(CXXFLAGS) -c -o build/cadb.o src/CADb.cpp -I ../liboctodroneparrot/include -I ../liboctodronecomms/include -I ../programs/include

aodvtest: AodvTestSim.o
	$(CXX) $(CXXFLAGS) -o bin/aodvtestsim build/AodvTestSim.o ../liboctodronecomms/src/Basic_message.cpp $(SIMLINK) $(SLDFLAGS)

basictest: BasicTestSim.o
	$(CXX) $(CXXFLAGS) -o bin/basictestsim build/BasicTestSim.o ../liboctodronecomms/src/Basic_message.cpp $(SIMLINK) $(SLDFLAGS)

scale: Scale.o
	$(CXX) $(CXXFLAGS) -o bin/scale build/Scale.o ../liboctodronecomms/src/Basic_message.cpp $(SIMLINK) $(SLDFLAGS)

parrottest: ParrotTestSimA.o ParrotTestSimB.o
	$(CXX) $(CXXFLAGS) -o bin/parrottestsima build/ParrotTestSimA.o ../liboctodronecomms/src/Basic_message.cpp $(PARLINK) $(PLDFLAGS)
	$(CXX) $(CXXFLAGS) -o bin/parrottestsimb build/ParrotTestSimB.o ../liboctodronecomms/src/Basic_message.cpp $(PARLINK) $(PLDFLAGS)

sensing: SensingSim.o
	$(CXX) $(CXXFLAGS) -o bin/sensingsim build/SensingSim.o ../liboctodronecomms/src/Basic_message.cpp $(SIMLINK) $(SLDFLAGS)

tod: toda.o todb.o
	$(CXX) $(CXXFLAGS) -o bin/toda build/toda.o ../liboctodronecomms/src/Basic_message.cpp $(PARLINK) $(PLDFLAGS)
	$(CXX) $(CXXFLAGS) -o bin/todb build/todb.o ../liboctodronecomms/src/Basic_message.cpp $(PARLINK) $(PLDFLAGS)

cad: cada.o cadb.o
	$(CXX) $(CXXFLAGS) -o bin/cada build/cada.o ../liboctodronecomms/src/Basic_message.cpp $(PARLINK) $(PLDFLAGS)
	$(CXX) $(CXXFLAGS) -o bin/cadb build/cadb.o ../liboctodronecomms/src/Basic_message.cpp $(PARLINK) $(PLDFLAGS)

clean:
	$(RM) build/*
	$(RM) bin/*
