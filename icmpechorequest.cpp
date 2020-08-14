#include "icmpechorequest.h"

icmpEchoRequest::icmpEchoRequest()
{

}

void icmpEchoRequest::getPacket(boost::asio::mutable_buffer &buff){
    setPacket();
}

void icmpEchoRequest::setPacket(){
    packet[0] = type = 8;
    packet[1] = code = 0;
    packet[2] = identifier = 0;
    packet[3] = sequenceNumber = 0;
    data = 77;
    checkSum = 0;

}
