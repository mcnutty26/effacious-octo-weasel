CXX		= g++
LINKFLAGS	= -L ../liboctodrone/lib -I ../liboctodrone/include -I include
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -fPIC -g
LIBFLAGS	= -loctodrone

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: lib

aodv:
	$(call colorecho,"Creating Aodv communication objects...")
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c src/aodv/Aodv.cpp -o build/Aodv.o $(LIBFLAGS)
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c src/aodv/Aodv_message.cpp -o build/Aodv_message.o $(LIBFLAGS)
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c src/aodv/Aodv_route.cpp -o build/Aodv_route.o $(LIBFLAGS)
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c src/aodv/Aodv_rreq.cpp -o build/Aodv_rreq.o $(LIBFLAGS)
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c src/aodv/Aodv_rrep.cpp -o build/Aodv_rrep.o $(LIBFLAGS)
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c src/aodv/Aodv_rerr.cpp -o build/Aodv_rerr.o $(LIBFLAGS)

basic:
	$(call colorecho,"Creating Basic communication objects...")
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c src/basic/Basic.cpp -o build/Basic.o $(LIBFLAGS)
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c src/basic/Basic_message.cpp -o build/Basic_message.o $(LIBFLAGS)

basic_addressed:
	$(call colorecho,"Creating Basic_addressed communication objects...")
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c src/basic_addressed/Basic_addressed.cpp -o build/Basic_message.o $(LIBFLAGS)
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c src/basic_addressed/Basic_addressed_message.cpp -o build/Basic_addressed_message.o $(LIBFLAGS)

lib: aodv basic basic_addressed
	$(call colorecho,"Creating communications library...")
	$(CXX) -shared -fPIC -o lib/liboctodronecomms.so build/*.o

clean:
	$(call colorecho,"Cleaning communications library...")
	$(RM) build/* 
	$(RM) lib/*
