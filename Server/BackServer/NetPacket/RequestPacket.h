#ifndef REQUESTPACKET_H
#define REQUESTPACKET_H
#include "PacketBase.h"


class RequestPacket : public PacketBase
{
public:
    RequestPacket(char *);
    RequestPacket(videoPacket *data,struct packet_work *work,videoPacketEnd *end);
    ~RequestPacket();

   inline int GetBodySize(){return bodysize;}
    inline bool isKeepActive()
    {
        if(m_packet->info.funcid==T_keepActive)
            isActiveKeep=true;
        else
            isActiveKeep=false;
        return isActiveKeep;
    }
    inline const char getfuncid()
    {
        return funcid;
    }

    inline bool isRight(){return isEffective;}
    inline int GetFd()
    {
        if(isEffective)
            return m_packet->info.client_fd;
        else
            return -1;
    }
    inline  videoPacket* GetPacket()
   {
       if(isEffective)
           return m_packet;
       else
           return NULL;
   }
    bool toPacket();
    virtual char * Tochar();
    virtual videoPacket* Getpacket();


private:
    int bodysize;
    bool isActiveKeep;
    bool isEffective;  //包是否有效
    char funcid;
};

#endif // REQUESTPACKET_H
