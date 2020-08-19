#include <QCoreApplication>

#include "icmpechorequest.h"
#include "myping.h"

#include <boost/thread.hpp>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const char ip[] = "google.com";

    myPing ping;
    if(ping.startEcho(ip))
        std::cout << ip << " replied" << std::endl;
    else
        std::cout << "No reply" << std::endl;

    std::cin.get();
    return 1;
}
