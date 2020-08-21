#include "myping.h"

/*      TODO

    - expand handleReceive method with proper reply decoding
    - add incorrect address handling for resolver

*/

void myPing::startEcho(){

    ip::icmp::resolver resolver(my_io_service);
    ep = *resolver.resolve(ip::icmp::v4(), ip, "");

    for(int requestNum = 0; requestNum < maxRequestNum; requestNum++){
        my_io_service.reset();
        replyFlag = false;

        start = boost::chrono::system_clock::now();

        // ConsoleMutex is used for std::iostream synchronization
        consoleMutex.lock();
        std::cout << "Sending " << requestNum + 1 << " packet to " << ip << std::endl;
        // Request is sent synchronously
        sendRequest();
        consoleMutex.unlock();

        // Timer drops socket after reply time is up
        // If reading from socket is successfull we cancel the timer
        boost::thread timerThread(&myPing::waitForReply, this);

        receiveReply();
        my_io_service.run();
        timerThread.join();
    }
}

void myPing::waitForReply(){
    boost::asio::io_context context;
    boost::asio::deadline_timer timer(context);
    timerPtr = &timer; // Storing pointer to cancel timer from other thread

    timer.expires_from_now(replyTime);
    timer.async_wait(boost::bind(&myPing::handleTimeout, this,
                                 boost::asio::placeholders::error));
    context.run();
}

void myPing::handleTimeout(const boost::system::error_code& error){
    // Checking for operation_aborted error because we expect it to be canceled
    if(error == boost::asio::error::operation_aborted)
        return;
    if(!replyFlag){
        consoleMutex.lock();
        std::cout << "Request timeout\n";
        consoleMutex.unlock();
        // Reading from socket will never stop if socket is empty so we have to stop it
        socket.cancel();
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
            consoleMutex.lock();
            boost::chrono::duration<double> elapsedTime = boost::chrono::system_clock::now() - start;
            std::cout << "Received a reply after " << elapsedTime.count() << " sec" << std::endl;

            // Not checking the reply for id and seq number YET
            // Just assuming that any reply from that ip is an echo reply

            /*
            unsigned char* output = new unsigned char[bytes_transfered];
                    std::istream is(&replyBuffer);
                    is.read(reinterpret_cast<char*>(output), static_cast<std::streamsize>(bytes_transfered));

                    std::cout << "Recieved\n";

                    for(int i = 0; i < static_cast<std::streamsize>(bytes_transfered); i++)
                        std::cout << i << ": " << static_cast<int>(output[i]) << "\n";
            */
            numOfReplies++;
            replyFlag = true;

            timerPtr->cancel();
            consoleMutex.unlock();
        }
    }
}

void myPing::receiveReply(){
    // Receiving 64KB
    socket.async_receive_from(replyBuffer.prepare(65536), ep,
                         boost::bind(&myPing::handleReceive, this,
                                     boost::asio::placeholders::error,
                                     boost::asio::placeholders::bytes_transferred));
}
