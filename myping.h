#ifndef MYPING_H
#define MYPING_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/thread.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

#include <iostream>
#include <icmpechorequest.h>

using namespace boost::asio;

class myPing
{
public:
    myPing(): socket(my_io_service, ip::icmp::v4()), numOfReplies(0){

    }
    ~myPing(){

    }
    bool startEcho(const char* destIp);
private:

    io_service my_io_service;
    boost::mutex *socketMutex;
    ip::icmp::socket socket;
    ip::icmp::endpoint ep;
    const char *ip;
    int numOfReplies;

    void handleReceive();
    void waitForReply(boost::posix_time::seconds replyTime);
    void sendRequest();
    void receiveReply();

    boost::asio::streambuf replyBuffer;
};

#endif // MYPING_H
