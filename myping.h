#ifndef MYPING_H
#define MYPING_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/thread.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include "icmpechorequest.h"

using namespace boost::asio;

class myPing
{
public:
    myPing(const char* destIp):
              socket(my_io_service, ip::icmp::v4()),
              replyTime(boost::posix_time::seconds(3)),
              ip(destIp),
              numOfReplies(0),
              maxRequestNum(3),
              replyFlag(false)
    {

    }
    ~myPing(){
        socket.close();
    }
    void startEcho();
    void printResults(){
        std::cout << "Received " << numOfReplies << " replies out of " << maxRequestNum << std::endl;
    }
private:

    io_service my_io_service;
    boost::mutex consoleMutex;
    ip::icmp::socket socket;
    ip::icmp::endpoint ep;
    boost::asio::deadline_timer *timerPtr;
    boost::posix_time::seconds replyTime;
    boost::asio::streambuf replyBuffer;
    boost::chrono::system_clock::time_point start;

    const char *ip;
    int numOfReplies;
    int maxRequestNum;
    bool replyFlag;

    void handleReceive(const boost::system::error_code& error, std::size_t bytes_transfered);
    void handleTimeout(const boost::system::error_code& error);
    void waitForReply();
    void sendRequest();
    void receiveReply();
};

#endif // MYPING_H
