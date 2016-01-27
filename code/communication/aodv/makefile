CXX		= g++
LINKFLAGS	= -L ../../simulator/build -I ../../simulator/src
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -fPIC
OBJ_FILES	= Aodv.o
OBJ_SET		= header_obj $(OBJ_FILES)
libraries	= -loctodrone

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: liboctodroneaodv

header_obj:
	$(call colorecho,"Compiling AODV objects...")

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c $< -o build/$@

liboctodrone:
	cd ../../simulator/src && $(MAKE) all

liboctodroneaodv: liboctodrone $(OBJ_FILES)
	$(call colorecho,"Creating libraries...")
	$(CXX) -shared -fPIC -o build/liboctodroneaodv.so $(addprefix build/, $(OBJ_FILES))

clean:
	$(RM) build/*
