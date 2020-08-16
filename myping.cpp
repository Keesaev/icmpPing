#include "myping.h"

bool myPing::startEcho(const char* ip){

    // send

    sendRequest(ip);

    // wait 3 seconds

    boost::asio::io_context context;
    boost::asio::deadline_timer timer(context);
    timer.expires_from_now(boost::posix_time::seconds(3));
    //timer.wait();

    // recieve

    if(recieveReply())
        return true;
    return false;
}

void myPing::sendRequest(const char* ip){

    ip::icmp::resolver resolver(my_io_service);
    ep = *resolver.resolve(ip::icmp::v4(), ip, "");

    icmpEchoRequest echoRequest;
    unsigned char *packet = echoRequest.getPacket();

    boost::asio::streambuf requestBuffer;
    std::ostream os(&requestBuffer);
    os.write(reinterpret_cast<const char*>(packet), 9);

    std::cout << "Pinging " << ip << std::endl;
    socket.send_to(requestBuffer.data(), ep);
}

bool myPing::recieveReply(){

    boost::asio::streambuf replyBuffer;

    std::size_t recSize = socket.receive_from(replyBuffer.prepare(static_cast<std::size_t>(1024)), ep);
    std::cout << "Recieved " << recSize << " butes\n";

    if(recSize == 0){
        std::cout << "No reply\n";
        return 0;
    }
    else {
        unsigned char* output = new unsigned char[recSize];
        std::istream is(&replyBuffer);
        is.read(reinterpret_cast<char*>(output), recSize);

        std::cout << "Recieved\n";

        for(int i = 0; i < recSize; i++)
            std::cout << i << ": " << (int)output[i] << "\n";

        std::cout << "(" << recSize << ") bytes\n"
                  << std::endl;
        return 1;
    }
}
