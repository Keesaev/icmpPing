#include "myping.h"

bool myPing::startEcho(const char* destIp){

    ip = destIp;

    int requestNum = 3; // Число попыток, которые мы предпример в качестве отсутствия ответа
    boost::posix_time::seconds replyTime = boost::posix_time::seconds(5); // Время на ответ

    for(int i = 0; i < requestNum && !numOfReplies; i++){

        ip::icmp::resolver resolver(my_io_service);
        ep = *resolver.resolve(ip::icmp::v4(), ip, "");

        std::cout << "Sending " << i + 1 << " packet to " << ip << std::endl;
        sendRequest();

        boost::thread receiveThread(&myPing::receiveReply, this);
        boost::thread timerThread(&myPing::waitForReply, this, replyTime);

        my_io_service.run();
        my_io_service.reset();

        receiveThread.join();
        timerThread.join();
    }

    if(numOfReplies)
        return true;
    return false;
}

void myPing::waitForReply(boost::posix_time::seconds replyTime){
    boost::asio::io_context context;
    boost::asio::deadline_timer timer(context);
    timerPtr = &timer;

    timer.expires_from_now(replyTime);
    timer.wait();

    context.run();

    if(numOfReplies == 0){
        //consoleMutex.lock();
        std::cout << "Request timeout\n";
        consoleMutex.unlock();
        //socket.cancel();
    }
}

void myPing::sendRequest(){

    icmpEchoRequest echoRequest;
    unsigned char *packet = echoRequest.getPacket();

    boost::asio::streambuf requestBuffer;
    std::ostream os(&requestBuffer);
    os.write(reinterpret_cast<const char*>(packet), 9);

    socket.send_to(requestBuffer.data(), ep);
}

void myPing::handleReceive(const boost::system::error_code& error, std::size_t bytes_transfered){

    if(!error){

        if(bytes_transfered){
            //consoleMutex.lock();
            std::cout << "Received " << bytes_transfered << " bytes\n";
            numOfReplies++;
            timerPtr->cancel();
            //consoleMutex.unlock();
        }
    }
}

void myPing::receiveReply(){

    socket.async_receive(replyBuffer.prepare(64),
                         boost::bind(&myPing::handleReceive, this,
                                     boost::asio::placeholders::error,
                                     boost::asio::placeholders::bytes_transferred));
}
