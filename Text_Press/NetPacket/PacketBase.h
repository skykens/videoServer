#ifndef PACKETBASE_H
#define PACKETBASE_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "public.h"
////
class PacketBase  //抽象类
{
public:
    PacketBase(char *src,int size);
    PacketBase();
    bool init(char *src);
    virtual void setBody(char *src,int size);
    virtual bool isError()=0;
    inline virtual bool isEnd(){return head->packet_seq==head->packet_sum;}
    inline virtual int getfunc(){return head->func_id;}
    inline virtual int getfd(){return head->fd;}
    inline virtual int size(){return m_size;}
    inline virtual char* Tochar(){return (char *)head;} //获得char[]

    virtual ~PacketBase();
protected:

    packet_head_t* head;
    packet_tail_t* tail;
    int m_size;
    char *body;
};
#endif // TEXTPACK_H
