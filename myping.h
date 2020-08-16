#ifndef MYPING_H
#define MYPING_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/asio/deadline_timer.hpp>

#include <iostream>
#include <icmpechorequest.h>

using namespace boost::asio;

class myPing
{
public:
    myPing(): socket(my_io_service, ip::icmp::v4()){

    }
    bool startEcho(const char* ip);
private:

    io_service my_io_service;
    boost::mutex *socketMutex;
    ip::icmp::socket socket;
    ip::icmp::endpoint ep;

    void sendRequest(const char* ip);
    bool recieveReply();
};

#endif // MYPING_H
