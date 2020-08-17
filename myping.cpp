#include "myping.h"

bool myPing::startEcho(const char* destIp){

    ip = destIp;

    int requestNum = 5; // Число попыток, которые мы предпример в качестве отсутствия ответа
    boost::posix_time::seconds replyTime = boost::posix_time::seconds(2); // Время на ответ

    for(int i = 0; i < requestNum && !numOfReplies; i++){

        std::cout << "Sending " << i + 1 << " packet to " << ip << std::endl;
        sendRequest();

        boost::thread receiveThread(&myPing::receiveReply, this);
        boost::thread timerThread(&myPing::waitForReply, this, replyTime);

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

    timer.expires_from_now(replyTime);
    timer.wait();

    if(numOfReplies == 0){
        std::cout << "Request timeout\n";
        socket.cancel();
    }
}

void myPing::sendRequest(){

    ip::icmp::resolver resolver(my_io_service);
    ep = *resolver.resolve(ip::icmp::v4(), ip, "");

    icmpEchoRequest echoRequest;
    unsigned char *packet = echoRequest.getPacket();

    boost::asio::streambuf requestBuffer;
    std::ostream os(&requestBuffer);
    os.write(reinterpret_cast<const char*>(packet), 9);

    socket.send_to(requestBuffer.data(), ep);
}

void myPing::handleReceive(){
    if(replyBuffer.size())
        numOfReplies++;
}

void myPing::receiveReply(){

    socket.async_receive(replyBuffer.prepare(1024),
                         boost::bind(&myPing::handleReceive, this));

    /*
    std::size_t recSize = socket.receive_from(replyBuffer.prepare(static_cast<std::size_t>(1024)), ep, 0, error);
    if(error && error != boost::asio::error::message_size)
        return 0;

    std::cout << "Recieved " << recSize << " bytes\n";

    if(recSize == 0){
        std::cout << "No reply\n";
        return 0;
    }
    else {
        unsigned char* output = new unsigned char[recSize];
        std::istream is(&replyBuffer);
        is.read(reinterpret_cast<char*>(output), recSize);

        std::cout << "Data:\n";

        for(int i = 0; i < recSize; i++)
            std::cout << i << ": " << (int)output[i] << "\n";

        std::cout << "(" << recSize << ") bytes\n"
                  << std::endl;
        return 1;
    }
    */
}
