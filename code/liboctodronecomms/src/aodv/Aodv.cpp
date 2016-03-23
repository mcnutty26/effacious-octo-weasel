///Implementation of the AODV routing protocol

#include "Aodv.hpp"
#include <iostream>
#include <sstream>
#include "../basic_addressed/Basic_addressed_message.hpp"
#include <chrono>
#include <thread>

Aodv::Aodv(Environment* env, std::string ip, std::atomic_flag* flag, bool debug): CommMod(env){
	ip_address = ip;
	environment = env;
	RANGE = 50;
	route_table = *(new std::map<std::string, Aodv_route*>);
	current_message = std::pair<std::string, std::string>("", "");
	state = 0;
	HELLO_INTERVAL = 2500;
	last_hello = -HELLO_INTERVAL;
	SEQUENCE_NUMBER = 1;
	ACTIVE_ROUTE_TIMEOUT = 5000;
	PATH_DISCOVERY_TIME = 5;
	BROADCAST_ID = 0;
	TTL = 5;
	lock = flag;
	logging = debug;
	log("init complete on thread ");
}

///Attribute extraction for AODV messages
/**
 * Takes in a message string and returns the first field of that message (semicolon delimited)
 */
std::string Aodv::get_attribute(std::string message){
	std::string attribute;
	std::stringstream attr;
	attr.str(message);
	std::getline(attr, attribute, ';');
	return attribute;
}

///Deserialization for route requests
/**
 * Takes a raw message string of a route reuest message and returns an AODV object representing that message
 */
Aodv_rreq* Aodv::deserialize_rreq(std::string message){
	std::string dst_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int dst_seq = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int ttl = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

	int hop_count = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string src_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int src_seq = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

	Aodv_rreq* result = new Aodv_rreq(hop_count, src_ip, dst_ip, src_seq, dst_seq, ttl);
	return result;
}

///Deserialization for route replies
/**
 * Takes a raw message string of a route reply message and returns an AODV object representing that message
 */
Aodv_rrep* Aodv::deserialize_rrep(std::string message){
	std::string dst_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int dst_seq = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int ttl = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

	int hop_count = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string src_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int life_time = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string lst_hop = Aodv::get_attribute(message).c_str();
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string nxt_hop = Aodv::get_attribute(message).c_str();
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	
	Aodv_rrep* result = new Aodv_rrep(hop_count, src_ip, dst_ip, lst_hop, dst_seq, life_time, ttl, nxt_hop);
	return result;
}

///Deserialization for route errors
/**
 * Takes a raw message string of a route error message and returns an AODV object representing that message
 */
Aodv_rerr* Aodv::deserialize_rerr(std::string message){
	std::string dst_ip = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int dst_seq = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	int ttl = atoi(Aodv::get_attribute(message).c_str());
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	
	Aodv_rerr* result = new Aodv_rerr(dst_ip, dst_seq, ttl);
	return result;
}

//Helper method for creating hello messages
/**
 * Creates a special route request for a route to this node, with TTL 1
 */
Aodv_rreq* Aodv::create_hello(){
	return Aodv::create_rreq(ip_address, ip_address, 1);
}

///Helper method for creating route requests
/**
 * Abstracts away the destination sequence number lookup for convienence
 */
Aodv_rreq* Aodv::create_rreq(std::string dst_ip, std::string src_ip, int ttl){
	int hop = 0;
	int dst_seq = 0;
	if (have_route(dst_ip)){
		dst_seq = route_table[dst_ip]->get_seq();
	}

	Aodv_rreq* to_send = new Aodv_rreq(hop, src_ip, dst_ip, SEQUENCE_NUMBER, dst_seq, ttl);
	return to_send;
}

///Checks if a route to the destination is known
/**
 * Determines if a route to the destination is known, and if that route is fresh
 */
bool Aodv::have_route(std::string ip){
	if (route_table.find(ip) != route_table.end()){// && route_table[ip]->get_life() + ACTIVE_ROUTE_TIMEOUT < environment->getTime()){
		return true;
	} else {
		return false;
	}
}

//Helper method for creating route replies
/**
 * Abstracts away next hop lookup for convienence
 */
Aodv_rrep* Aodv::create_rrep(std::string dst_ip, std::string src_ip, int ttl){
	int hop = 0;
	int dst_seq = route_table[dst_ip]->get_seq();
	int life_time = 0;
	std::string next_hop = route_table[dst_ip]->get_next_hop();

	Aodv_rrep* to_send = new Aodv_rrep(hop, src_ip, dst_ip, ip_address, dst_seq, life_time, ttl, next_hop);
	return to_send;
}

///Helper method for creating route errors
/**
 * Abstracts away the destination sequence number lookup for convienence
 */
Aodv_rerr* Aodv::create_rerr(std::string dst_ip, int ttl){
	int dst_seq = 0;
	if (have_route(dst_ip)){
		dst_seq = route_table[dst_ip]->get_seq();
	}

	Aodv_rerr* to_send = new Aodv_rerr(dst_ip, dst_seq, ttl);
	return to_send;
}

///Creates a route in the routing table
/**
 * Adds in the standard route timeout and ensures that all variables are set to prevent memory issues later
 */
void Aodv::add_route(std::string ip, int dest_seq, int hop_count, std::string next_hop){
	Aodv_route* route = new Aodv_route(dest_seq, hop_count, next_hop, ACTIVE_ROUTE_TIMEOUT);
	route_table.insert(std::pair<std::string, Aodv_route*>(ip, route));
	log("ADDED " + ip + " VIA " + next_hop);
}

///Handle an RREQ that was received
/**
 * First we check if the message was a hello message, and if so we always respond to it
 * If the message was a normal request, then we either answer it (if we have the info) or forward it if we do not
 * Note that non-hello RREQs will be dropped if we are currently trying to send a message
 */
void Aodv::process_rreq(Aodv_rreq* message){
	log("rec'd a RREQ packet from " + message->get_source_ip() + " for " + message->get_dest_ip());

	//process hello messages
	if (message->get_source_ip() == message->get_dest_ip()){
		if (have_route(message->get_source_ip()) && message->get_source_seq() > route_table[message->get_source_ip()]->get_seq()){
			//our info is out of date, so update it
			route_table.erase(message->get_source_ip());
			add_route(message->get_source_ip(), message->get_dest_seq(), 1, message->get_source_ip());
			log("updated info for " + message->get_source_ip());
		} else if (!have_route(message->get_source_ip())) {
			//our info is missing, so create it
			add_route(message->get_source_ip(), message->get_dest_seq(), 1, message->get_source_ip());
			log("created info for " + message->get_source_ip());
		}
		Aodv_rrep* route_data = create_rrep(message->get_source_ip(), message->get_dest_ip(), message->get_hop_count());
		broadcast(route_data->to_string());
		log("Replied to hello message from " + message->get_source_ip());
	} else if (state == 0){
		if (have_route(message->get_dest_ip())){
			Aodv_rrep* route_data = create_rrep(message->get_source_ip(), message->get_dest_ip(), TTL);
			log("Answering  multihop route request from " + message->get_source_ip());
			broadcast(route_data->to_string());
		} else if (message->get_source_ip() != current_message.second && message->get_ttl() > 0){
			state = 2;
			Aodv_rreq* route_data = create_rreq(message->get_dest_ip(), message->get_source_ip(), message->get_ttl() - 1);
			current_message.second = message->get_source_ip();
			log("Forwarding multihop route request from " + message->get_source_ip() + " to " + message->get_dest_ip());
			broadcast(route_data->to_string());
		}
	}
}

///Handle an RREP that was received
/**
 * First we check if the message contains new information about other nodes, and if so we always update our routing table
 * If the message was a response to a request we initiated, then we should send our data packet.
 * If the message was a response to a request we forwarded for another node, then we should pass it on
 * Note that nodes will only act as a middle hop for one message at a time (other reponses will be dropped)
 */
void Aodv::process_rrep(Aodv_rrep* message){
	log("rec'd a RREP packet from " + message->get_source_ip() + " / " + message->get_last_hop());

	//check our info on the sender
	if (false){
		//our info is out of date, so update it
		route_table.erase(message->get_source_ip());
		add_route(message->get_source_ip(), message->get_dest_seq(), 1, (message->get_last_hop()));
		log("updated info for " + message->get_source_ip());
	} else if (!have_route(message->get_source_ip()) && message->get_source_ip() != ip_address) {
		//our info is missing, so create it
		std::string last_hop = (message->get_source_ip() == ip_address ? ip_address : message->get_last_hop());
		add_route(message->get_source_ip(), message->get_dest_seq(), 1, last_hop);
		log("created info for " + message->get_source_ip());
	}

	if(state == 1 && message->get_dest_ip() == ip_address && message->get_source_ip() != ip_address){
		//we were waiting for a route
		state = 0;
		std::string data_message = "DATA;" 
			+ current_message.second
			+ ";" + route_table[current_message.second]->get_next_hop()
			+ ";" + ip_address 
			+ ";" + current_message.first;
		broadcast(data_message);
		log("Data packet sent to " + current_message.second + " via " + route_table[current_message.second]->get_next_hop());
		
	} else if (state == 2 && current_message.second == message->get_dest_ip() && message->get_ttl() > 0){
		//we previously forwarded a multihop route request
		Aodv_rrep* route_info = create_rrep(message->get_dest_ip(), message->get_source_ip(), message->get_ttl() - 1);
		log("Sending reply for previously forwarded mumtihop route request to " + message->get_dest_ip());
		state = 0;
		broadcast(route_info->to_string());
	}
}

///Handle an data packet that was received
/**
 * First we check if the message was for us, and if so we deliver the contents to our messageable
 * If the message is destined for another node and we are specified as the next hop, then we forward that packet to the next hop according to our own routing table
 * Note that messages destined for other nodes that we are not specified as a next hop for will be dropped
 */
void Aodv::process_data(std::string message){
	std::string destination = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string next_hop = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string source = Aodv::get_attribute(message);
	message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
	std::string content = Aodv::get_attribute(message);

	log("rec'd a DATA packet from " + source + ", via " + next_hop);

	if (destination == ip_address){
		log("The data packet is for this node");
		state = 0;
		messageable->push_message(new Basic_addressed_message(content, destination, source));
	} else if (next_hop == ip_address){
		log("Forwarding data packet to " + destination + " via " + route_table[destination]->get_next_hop());
		std::string data_message = "DATA;" 
			+ destination
			+ ";" + route_table[destination]->get_next_hop()
			+ ";" + source 
			+ ";" + content;
		broadcast(data_message);
	}
}

///Handle an RERR that was received
/**
 * This functionality os not yet implemented
 */
void Aodv::process_rerr(Aodv_rerr* message){
	log("rec'd a RERR packet");
	(void)message;
}

///The main communications loop which handles incomming and outgoing messages
/**
 * Every loop we check to see if we should send a hello, based on the hello interval
 * Next, any incomming messages are deserialized and handled appropriately
 * If our messageable told us to shut down, the communications module exits
 * Next, any outgoing messages are either immediately sent (if we have a route to the destination already) or a route request is distributed (if we do not have a route)
 */
void Aodv::comm_function(){
	while (true){
		if (last_hello + HELLO_INTERVAL < environment->getTime()){
			log("sending hello");
			Aodv_rreq* hello = create_hello();
			last_hello = environment->getTime();
			broadcast(hello->to_string());
		}

		while (!inQueue.empty()){
			//get the message from the environment
			std::string message = inQueue.front();
			inQueue.pop();

			//determine what type of message it is
			std::string m_type = Aodv::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);

			if (m_type == "RREQ"){
				process_rreq(deserialize_rreq(message));
			} else if (m_type == "RREP"){
				process_rrep(deserialize_rrep(message));
			} else if (m_type == "RERR"){
				process_rerr(deserialize_rerr(message));
			} else if (m_type == "DATA"){
				process_data(message);
			} else {
				log("rec'd and dropped unknown packet");
			}
		}
		while (!outQueue.empty() && state == 0){
			std::string message = outQueue.front()->to_string();

			//exit if our messageable sent us a kill packet
			if (message == "KILL"){
				log("exiting");
				return;
			}

			//get the message from the messageable if we are not currently processing a message
			std::string destination = Aodv::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
			std::string source = Aodv::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
			std::string content = Aodv::get_attribute(message);
			message.erase(message.begin(), message.begin() + message.find_first_of(";") + 1);
			outQueue.pop();

			log("Starting AODV for message to " + destination);

			//update internal state
			state = 1;

			if (have_route(destination)){
				state = 0;
				std::string data_message = "DATA;" 
					+ destination
					+ ";" + route_table[destination]->get_next_hop()
					+ ";" + ip_address 
					+ ";" + content;
				broadcast(data_message);
				log("data packet sent with exitsing info via " + route_table[destination]->get_next_hop());
			} else {
				current_message.first = content;
				current_message.second = destination;
				Aodv_rreq* route_request = create_rreq(destination, ip_address, TTL);
				state = 1;
				log("Sent out a route request");
				broadcast(route_request->to_string());
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

///Helper function to log internal information
/**
 * Makes use of the stdout lock we were passed on creation to make sure that only one thread is printing at any one time
 * Also prints the ip of the communications module and the current environment time to help with debugging
 */
void Aodv::log(std::string log_message){
	if (logging){
		while(lock->test_and_set()){}
		std::ostringstream time_stream;
		time_stream << environment->getTime();
		std::string time_string  = time_stream.str();
		std::cout << "(" + time_string + ")aodv@" << ip_address << ": " << log_message << std::endl;
		lock->clear();
	}
}

///Helper function to broadcast a message through the environment
/**
 * Broadcast requires the coordinates of the broadcasting unit which can be unwieldy to do every time
 * This process is simplified by wrapping it in a helper function
 */
void Aodv::broadcast(std::string message){
	//Update our position
	double xpos = messageable->getX();
	double ypos = messageable->getY();
	double zpos = messageable->getZ();
	environment->broadcast(message, xpos, ypos, zpos, RANGE, this);
}

