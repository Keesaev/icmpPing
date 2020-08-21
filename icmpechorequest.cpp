#include "icmpechorequest.h"


/*      TODO:


    - set sequence number method
    - set id method
    - set data method
    - calculate check sum method


*/

unsigned char* icmpEchoRequest::getPacket(){
    setPacket();
    return packet;
}

void icmpEchoRequest::setPacket(){
    /*
      ICMP echo request
      --9 bytes total--

      check sum is not calculated atm
      for now it's just fixed just like the rest of packet

     0   type            = 1 byte   = 8     = 0x8
     1   code            = 1 byte   = 0     = 0x0
     2 3 check sum       = 2 bytes  = 31994 = 0x7CFA
     4 5 id              = 2 bytes  = 5     = 0x5
     6 7 sequence number = 2 bytes  = 0     = 0x0
     8   data            = 1 byte   = 123   = 0x7B

    */
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
