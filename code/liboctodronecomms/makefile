CXX		= g++
LDFLAGS	= -L ../liboctodrone/lib -I ../liboctodrone/include -I include -loctodrone
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -fPIC -g

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

vpath %.cpp	src
vpath %.hpp	include
vpath %.o	build

all: lib

aodv: Aodv.o Aodv_message.o Aodv_route.o Aodv_rreq.o Aodv_rrep.o Aodv_rerr.o
	$(call colorecho,"Creating Aodv communication objects...")

Aodv.o: Aodv.cpp Aodv.hpp
	$(CXX) $(CXXFLAGS) -c src/Aodv.cpp -I include -I ../liboctodrone/include -o build/Aodv.o

Aodv_message.o: Aodv_message.cpp Aodv_message.hpp
	$(CXX) $(CXXFLAGS) -c src/Aodv_message.cpp -I include -I ../liboctodrone/include -o build/Aodv_message.o

Aodv_route.o: Aodv_route.cpp Aodv_route.hpp
	$(CXX) $(CXXFLAGS) -c src/Aodv_route.cpp -I include -I ../liboctodrone/include -o build/Aodv_route.o

Aodv_rreq.o: Aodv_rreq.cpp Aodv_rreq.hpp
	$(CXX) $(CXXFLAGS) -c src/Aodv_rreq.cpp -I include -I ../liboctodrone/include -o build/Aodv_rreq.o

Aodv_rrep.o: Aodv_rrep.cpp Aodv_rrep.hpp
	$(CXX) $(CXXFLAGS) -c src/Aodv_rrep.cpp -I include -I ../liboctodrone/include -o build/Aodv_rrep.o

Aodv_rerr.o: Aodv_rerr.cpp Aodv_rerr.hpp
	$(CXX) $(CXXFLAGS) -c src/Aodv_rerr.cpp -I include -I ../liboctodrone/include -o build/Aodv_rerr.o

basic: Basic.o Basic_message.o
	$(call colorecho,"Creating Basic communication objects...")

Basic.o: Basic.cpp Basic.hpp
	$(CXX) $(CXXFLAGS) -c src/Basic.cpp -I include -I ../liboctodrone/include -o build/Basic.o

Basic_message.o: Basic_message.cpp Basic_message.hpp
	$(CXX) $(CXXFLAGS) -c src/Basic_message.cpp -I include -I ../liboctodrone/include -o build/Basic_message.o

basic_addressed: Basic_addressed.o Basic_addressed_message.o
	$(call colorecho,"Creating Basic_addressed communication objects...")

Basic_addressed.o: Basic_addressed.cpp Basic_addressed.hpp
	$(CXX) $(CXXFLAGS) -c src/Basic_addressed.cpp -I include -I ../liboctodrone/include -o build/Basic_message.o

Basic_addressed_message.o: Basic_addressed_message.cpp Basic_addressed_message.hpp
	$(CXX) $(CXXFLAGS) -c src/Basic_addressed_message.cpp -I include -I ../liboctodrone/include -o build/Basic_addressed_message.o

lib: aodv basic basic_addressed
	$(call colorecho,"Creating communications library...")
	$(CXX) -shared -fPIC -o lib/liboctodronecomms.so build/*.o 

clean:
	$(call colorecho,"Cleaning communications library...")
	$(RM) build/* 
	$(RM) lib/*
