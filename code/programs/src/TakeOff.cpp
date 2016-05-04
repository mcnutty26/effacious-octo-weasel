#include "TakeOff.hpp"
  #include <iostream>
  #include <thread>
  #include <chrono>
  #include <Basic_message.hpp>
  

  TakeOff::TakeOff(CommMod* cm, double xp, double yp, double zp, double speed, Environment* env, bool sink_node): Drone(cm, xp, yp, zp, speed, env){
          m_sink_node = sink_node;
  };
  

  bool TakeOff::message_callback(Message*){
      return false;
  }
  

  void TakeOff::run(){
          if (m_sink_node){
                  std::cout << "TakeOff: sink waiting for message" << std::endl;
                  if (wait_for_message()->to_string() == "TEST"){
                          std::cout << "TakeOff: received message" << std::endl;
			  
                          turn(45);
                          while(!hasFinishedMoving()){}
                          move(Direction::FORWARD, 0.5, 4);
                          while(!hasFinishedMoving()){}
                          turn(-45);
                          while(!hasFinishedMoving()){}
                          move(Direction::FORWARD, 0.5, 1);
			  while(!hasFinishedMoving()){}
			  move(Direction::FORWARD, 0.5, 1);
			  while(!hasFinishedMoving()){}
			  turn(90);
			  while(!hasFinishedMoving()){}
			  move(Direction::FORWARD, 0.5, 1);
			  while(!hasFinishedMoving()){}
                  }
          } else {
                  std::cout << "TakeOff: source sending message" << std::endl;
                  send_message(new Basic_message("TEST"));
		  
		  turn(-45);
		  while(!hasFinishedMoving()){}
		  move(Direction::FORWARD, 0.5, 4);
		  while(!hasFinishedMoving()){}
		  turn(45);
		  while(!hasFinishedMoving()){}
		  move(Direction::FORWARD, 0.5, 1);
		  while(!hasFinishedMoving()){}
		  move(Direction::FORWARD, 0.5, 1);
		  while(!hasFinishedMoving()){}
		  turn(90);
		  while(!hasFinishedMoving()){}
		  move(Direction::FORWARD, 0.5, 1);
		  while(!hasFinishedMoving()){}
          }
          send_message(new Basic_message("KILL"));
          std::cout << "TakeOff: exiting" << std::endl;
          kill();
  }
