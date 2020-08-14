#ifndef ICMPPACKET_H
#define ICMPPACKET_H

#include <string.h>
#include <iostream>

#include <boost/asio/buffer.hpp>
#include <boost/variant.hpp>
#include <boost/asio/buffer.hpp>

class icmpPacket
{
public:
    icmpPacket(){}
    virtual void getPacket(boost::asio::mutable_buffer &buf){};
    virtual ~icmpPacket(){};
protected:
    virtual void setPacket(){};
    // unsigned char = 1 byte
    unsigned char type;
    unsigned char code;
    // unsigned short = 2 bytes
    unsigned short identifier;
    unsigned short sequenceNumber;
    unsigned short data;
    unsigned short checkSum;

};

#endif // ICMPPACKET_H
