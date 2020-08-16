#include <QCoreApplication>

#include "icmpechorequest.h"
#include "myping.h"

#include <boost/thread.hpp>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const char ip[] = "localhost";

    myPing ping;
    ping.startEcho(ip);

    return 1;
}
