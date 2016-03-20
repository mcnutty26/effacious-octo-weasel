#include "AodvComms.hpp"
#include <iostream>
#include <Basic_message.hpp>
#include <Basic_message_addressed.hpp>
#include <chrono>
#include <thread>
#include <atomic>

AodvComms::AodvComms(CommMod* cm, double xp, double yp, double zp, double speed, Environment* env, int task, int* flag, std::atomic_flag* lock): Drone(cm, xp, yp, zp, speed, env){
	m_task = task;
	m_flag = flag;
	m_lock = lock;
	m_env = env;
};

bool AodvComms::message_callback(Message*){
    return false;
}

void AodvComms::run(){
	switch(m_task){
		case 0:
			//while(m_lock->test_and_set()){}
			std::cout << "Sink waiting for message" << std::endl;
			std::cout << wait_for_message()->to_string() << std::endl;
			//m_lock->clear();
			*m_flag = 1;
			break;
		case 1:
			while(m_env->getTime() < 500){}
			while(m_lock->test_and_set()){}
			std::cout << "Source sending message" << std::endl;
			m_lock->clear();
			send_message(new Basic_message_addressed("TEST MESSAGE PLEASE IGNORE", "10.0.0.1"));
			break;
		case -1:
			while (*m_flag != 1){
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
	}
	send_message(new Basic_message("KILL"));
}
