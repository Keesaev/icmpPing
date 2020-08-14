#include "myping.h"

bool myPing::startEcho(const char* ip){

    ip::icmp::resolver resolver(*io_service);
    ip::icmp::endpoint ep = *resolver.resolve(ip::icmp::v4(), ip, "");

    // Оказывается, на линуксе icmp сокет может создаваться только с рут правами
    ip::icmp::socket socket(*io_service, ip::icmp::v4());

    // Придумать как покрасивше привести поля к массиву, а затем к буферу, возможно
    // boost::array<boost::any, 6>, а может два массива

    // send

    // recieve

    // return 1 in case of success, 0 in case of failure

    return true;
}
