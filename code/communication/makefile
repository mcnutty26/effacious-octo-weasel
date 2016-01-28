CXX		= g++
LINKFLAGS	= -L ../../simulator/build -I ../../simulator/src
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -fPIC
OBJ_FILES	= aodv/build/*.o basic/build/*.o
libraries	= -loctodrone

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: liboctodronecomms

makeobjs:
	$(call colorecho,"Compiling communcations objects...")
	cd aodv && $(MAKE) all
	cd basic && $(MAKE) all

liboctodrone:
	cd ../simulator/src && $(MAKE) all

liboctodronecomms: liboctodrone makeobjs
	$(call colorecho,"Creating communications library...")
	$(CXX) -shared -fPIC -o liboctodronecomms.so $(OBJ_FILES)

clean:
	$(RM) liboctodronecomms.so
