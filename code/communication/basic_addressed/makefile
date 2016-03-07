CXX		= g++
LINKFLAGS	= -L ../../simulator/build -I ../../simulator
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -fPIC
OBJ_FILES	= Basic_addressed.o Basic_message_addressed.o
OBJ_SET		= header_obj $(OBJ_FILES)
libraries	= -loctodrone

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: $(OBJ_SET)

header_obj:
	$(call colorecho,"Compiling basic objects...")

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(libraries) -c $< -o build/$@

clean:
	$(RM) build/*
