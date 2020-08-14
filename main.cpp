#include <QCoreApplication>

#include "icmppacket.h"
#include "myping.h"

#include <boost/thread.hpp>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    boost::mutex consoleMutex;
    myPing ping(&consoleMutex);

    ping.startEcho("localhost");

    return 0;
}
