#include <QCoreApplication>

#include "icmpechorequest.h"
#include "myping.h"

#include <boost/thread.hpp>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const char *ip;

    if(argc < 2){
        std::cout << "Type \"myPing <ip_address>\"\n";
        return 0;
    }
    else {
        ip = argv[1];
    }

    myPing ping(ip);
    ping.startEcho();
    ping.printResults();

    return 0;
}
