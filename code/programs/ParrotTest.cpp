#include "ParrotTest.hpp"
#include <iostream>

ParrotTest::ParrotTest(CommMod* cm, double xp, double yp, double zp, double speed, Environment* env): Drone(cm, xp, yp, zp, speed, env){
};

bool ParrotTest::message_callback(Message*){
    return false;
}

void ParrotTest::run(){
	move(Direction::FORWARD, 10.0, 10.0);
	kill();
}

