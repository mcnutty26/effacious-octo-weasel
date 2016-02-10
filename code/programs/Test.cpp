#include "Test.hpp"
#include <iostream>

Test::Test(CommMod* cm, double xp, double yp, double zp, double speed, Environment* env, bool sink): Drone(cm, xp, yp, zp, speed, env){
	sink_node = sink;
};

bool Test::message_callback(Message*){
    return false;
}

void Test::run(){
	if (sink_node){
	    std::cout << "SINK" << std::endl;
	} else {
	    std::cout << "SOURCE" << std::endl;
	}
}

int main(int argv, char* argc[]){
	Environment env = new Environment()
}
