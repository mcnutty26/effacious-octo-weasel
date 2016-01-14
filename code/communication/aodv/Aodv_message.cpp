#include "Aodv_message.hpp"

Aodv_message(std::string dst_ip, int dst_seq, int time){
    dest_ip = dst_ip;
    dest_seq = dst_seq;
    time_stamp = time;
}
