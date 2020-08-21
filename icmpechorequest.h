#ifndef ICMPECHOREQUEST_H
#define ICMPECHOREQUEST_H

#include <boost/asio.hpp>

#include <iostream>

class icmpEchoRequest
{
public:
    icmpEchoRequest(){}
    unsigned char* getPacket();
    ~icmpEchoRequest(){}
private:
    void setPacket();
    unsigned char packet[9];
};

#endif // ICMPECHOREQUEST_H
