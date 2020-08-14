#ifndef ICMPECHOREQUEST_H
#define ICMPECHOREQUEST_H

#include "icmppacket.h"

#include <boost/array.hpp>
#include <boost/any.hpp>

class icmpEchoRequest : public icmpPacket
{
public:
    icmpEchoRequest();
    void getPacket(boost::asio::mutable_buffer &buff);
    ~icmpEchoRequest(){};
private:
    void setPacket();
    boost::array<boost::any, 6> packet;

};

#endif // ICMPECHOREQUEST_H
