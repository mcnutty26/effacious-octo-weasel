CXX		= g++
LINKFLAGS	=
CXXFLAGS	= -std=c++11 -Werror -Wall -Wextra -pthread -fPIC -g
objects		= Messageable Message CommMod  BaseStation Environment Drone
libraries	= -lglfw3 -lglew32 -lgdi32 -lopengl32
headers		= Messageable.hpp CommMod.hpp Message.hpp BaseStation.hpp Drone.hpp
exe		=

OBJ_FILES = BaseStation.o CommMod.o Drone.o Environment.o Message.o Messageable.o
OBJ_SET = header_obj $(OBJ_FILES)

define colorecho
      @tput setaf 32
      @echo $1
      @tput sgr0
endef

all: libdrone

header_obj:
	$(call colorecho,"Compiling simulator objects...")

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o build/$@

libdrone: $(OBJ_SET)
	$(call colorecho,"Creating simulator library...")
	$(CXX) -shared -fPIC -o build/liboctodrone.so $(addprefix build/, $(OBJ_FILES))

clean:
	$(RM) build/*
