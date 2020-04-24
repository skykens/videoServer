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
    PacketBase(int funcid,int fd);
    virtual int getDataSize()const =0;  //返回data包的大小
    virtual bool getData(void *) const =0;
    virtual int SerializeToArray(void *data,int size);//获得字节流
    inline virtual int getfunc(){return head.func_id;}
    inline virtual int getfd(){return head.fd;}
    inline void setErrmsg(const char * errmsg){head.error_code=1;strcpy(head.error_msg,errmsg);}
    void setCliend(int fd);
    virtual ~PacketBase();
protected:
    packet_head_t head;
    packet_tail_t tail;
};
#endif // TEXTPACK_H
