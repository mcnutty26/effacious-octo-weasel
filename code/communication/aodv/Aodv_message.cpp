#include "Aodv_message.hpp"

Aodv_message(std::string dst_ip, int dst_seq, int ttl_time){
    dest_ip = dst_ip;
    dest_seq = dst_seq;
    ttl = ttl_time;
    using Message::Mesage();
}

std::string get_dest_ip(){
  return dest_ip;
}

int get_dest_seq(){
  return dest_seq;
}
