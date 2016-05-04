#include "CollisionAvoidance.hpp"
  #include <iostream>
  #include <thread>
  #include <chrono>
  #include <Basic_message.hpp>
  

  CollisionAvoidance::CollisionAvoidance(CommMod* cm, double xp, double yp, double zp, double speed, Environment* env, bool sink_node): Drone(cm, xp, yp, zp, speed, env){
          m_sink_node = sink_node;
  };
  

  bool CollisionAvoidance::message_callback(Message*){
      return false;
  }
  

  void CollisionAvoidance::run(){
          if (m_sink_node){
                  std::cout << "CollisionAvoidance: sink waiting for message" << std::endl;
                  if (wait_for_message()->to_string() == "TEST"){
                          std::cout << "CollisionAvoidance: received message" << std::endl;
			  
                         
                          move(Direction::FORWARD, 0.5, 4);
                          while(!hasFinishedMoving()){}
                          move(Direction::UP, 0.5, 1);
                          while(!hasFinishedMoving()){}
                          move(Direction::FORWARD, 0.5, 1);
                          while(!hasFinishedMoving()){}
                          
                          
                  }
          } else {
                  std::cout << "CollisionAvoidance: source sending message" << std::endl;
                  send_message(new Basic_message("TEST"));
		  
		  move(Direction::FORWARD, 0.5, 1);
                  while(!hasFinishedMoving()){}
                  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		  move(Direction::FORWARD, 0.5, 1);
                  while(!hasFinishedMoving()){}
		  
		 
          }
          send_message(new Basic_message("KILL"));
          std::cout << "CollisionAvoidance: exiting" << std::endl;
          kill();
  }