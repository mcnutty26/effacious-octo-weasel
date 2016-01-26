CXX		= g++
LINKFLAGS	=
CXXFLAGS	= -std=c++1y -Werror -Wall -Wextra -pthread
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
	$(CXX) $(CXXFLAGS) -c $< -o ../build/$@

libdrone: $(OBJ_SET)
	$(call colorecho,"Creating libraries...")
	ar rcs ../build/libdrone.a $(addprefix ../build/, $(OBJ_FILES))

clean:
	$(RM) ../build/*
