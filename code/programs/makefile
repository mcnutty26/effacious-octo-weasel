CXX		= g++
LINKFLAGS	= -L ../simulator/build -I ../simulator -L ../communication/build -I ../communication/basic
LIBFLAGS	= -loctodrone -loctodronecomms -lpthread
CXXFLAGS	= -std=c++11 -Werror -Wextra

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

program: 
	$(call colorecho,"Compiling drone routines...")
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) $(LINKFLAGS) -c -o build/Test.o Test.cpp

exe:
	$(call colorecho,"Creating executables...")
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(LIBFLAGS) -I ../ -o build/test Test_exe.cpp build/Test.o

complete: deps program exe

clean:
	$(RM) build/*
	cd ../simulator && $(MAKE) clean
	cd ../communication && $(MAKE) clean
