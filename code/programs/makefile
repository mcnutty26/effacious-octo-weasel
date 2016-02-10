CXX		= g++
LINKFLAGS	= -L ../simulator/build -I ../simulator -L ../communication/ -I ../communication/basic
LIBFLAGS	= -loctodrone -loctodronecomms -lpthread
CXXFLAGS	= -std=c++11 -Werror -Wextra -fPIC
EXE_FILES	= test
libraries	= -loctodrone

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: complete

deps:
	cd ../simulator && $(MAKE)
	sudo cp ../simulator/build/liboctodrone.so /usr/local/lib
	cd ../communication && $(MAKE)
	sudo cp ../communication/liboctodronecomms.so /usr/local/lib

exe:
	$(call colorecho,"Creating test binary...")
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(LIBFLAGS) -o test Test.cpp

complete: deps exe

clean:
	$(RM) test
