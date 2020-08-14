#ifndef MYPING_H
#define MYPING_H

#include <boost/asio/connect.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/thread/mutex.hpp>

#include <iostream>

#include <icmppacket.h>
#include <icmpechorequest.h>

using namespace boost::asio;

class myPing
{
public:
    myPing(boost::mutex *consoleMutex): consoleMutex(consoleMutex){
        io_service = new boost::asio::io_service();
    }

    bool startEcho(const char* ip);

private:
    boost::asio::io_service *io_service;
    boost::mutex *consoleMutex;

};

#endif // MYPING_H
