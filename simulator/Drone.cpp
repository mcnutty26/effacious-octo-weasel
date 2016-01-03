#include "Drone.hpp"

void Drone::send_message(std::string contents)
{
	communicationsModule.outQueue.push(contents);
}
