CXX		= g++
LINKFLAGS	= -L ../../simulator/build -I ../../simulator
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -fPIC
OBJ_FILES	= aodv/build/*.o basic/build/*.o basic_addressed/build/*.o
libraries	= -loctodrone

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: liboctodronecomms

makeobjs:
	cd aodv && $(MAKE) all
	cd basic && $(MAKE) all
	cd basic_addressed && $(MAKE) all

liboctodronecomms: makeobjs
	$(call colorecho,"Creating communications library...")
	$(CXX) -shared -fPIC -o build/liboctodronecomms.so $(OBJ_FILES)

clean:
	$(RM) build/*
