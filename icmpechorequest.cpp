#include "icmpechorequest.h"

unsigned char* icmpEchoRequest::getPacket(){
    setPacket();
    return packet;
}

void icmpEchoRequest::setPacket(){

    // 0 type = 8 = 0x8
    // 1 code = 0
    // 2 3 check sum = 2 bytes = 9 = 0x9
    // 4 5 id = 2 bytes = 5 = 0x5
    // 6 7 sequence number = 2 bytes = 0
    // 8 9 data = 1 byte = 123 = 0x7B

    packet[0] = 0x8;

    packet[1] = 0x0;

    packet[2] = 0x7C;
    packet[3] = 0xFA;

    packet[4] = 0x0;
    packet[5] = 0x5;

    packet[6] = 0x0;
    packet[7] = 0x0;

    packet[8] = 0x7B;
}
