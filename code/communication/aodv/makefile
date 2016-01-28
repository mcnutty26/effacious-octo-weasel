CXX		= g++
LINKFLAGS	= -L ../../simulator/build -I ../../simulator/src
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -fPIC
OBJ_FILES	= Aodv.o Aodv_message.o Aodv_route.o Aodv_rreq.o Aodv_rrep.o Aodv_rerr.o
OBJ_SET		= header_obj $(OBJ_FILES)
libraries	= -loctodrone

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: $(OBJ_SET)

header_obj:
	$(call colorecho,"Compiling aodv objects...")

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c $< -o build/$@

clean:
	$(RM) build/*
