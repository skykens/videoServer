#ifndef BUSYPACKET_H
#define BUSYPACKET_H

#include "cbasepacket.h"
#include "public.h"
#include <QDateTime>
#include <string.h>
#include <QDebug>
//正在工作的包
class BusyPacket : public CBasePacket
{
public:
    BusyPacket(int no = 0);
    ~BusyPacket();
    int pack();
    int unpack();
    void hreat_Packet();
    void login_Packet();
    void register_Packet();
    void class_Packet();
    void type_Packet();
    void area_Packet();
    void video_list_Packet();
    void play_flowid_Packet();
    void video_play_Packet();
    void time_flowid_Packet();
    void video_time_Packet();
    char *getBody();
public:
    Packet_Head_T head;
    Packet_Tail_T tail;

    char body[sizeof(packet_all_t) - sizeof(Packet_Head_T) - sizeof(packet_tail_t)];
};

#endif // BUSYPACKET_H
