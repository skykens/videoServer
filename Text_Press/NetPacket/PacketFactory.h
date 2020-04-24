#ifndef PACKETFACTORY_H
#define PACKETFACTORY_H
#include "Factory.h"
#include "PacketBase.h"
#include "NetPacket.h"

class PacketFactory : public Factory
{
public:
     PacketFactory();
    PacketBase *CreateLogin(char *src,int size)
    {
        return new LoginPacket(src,size);
    }
    PacketBase *CreateRegis(char *src,int size)
    {
        return new RegisPacket(src,size);
    }
    PacketBase *CreateKeepActive(char *src,int size)
    {
        return new KeepActivePacket(src,size);
    }
    PacketBase *CreateClass(char *src,int size)
    {
        return new ClassPacket(src,size);
    }
    PacketBase *CreateVideoType(char *src,int size)
    {
        return new VideoTypePacket(src,size);
    }
    PacketBase *CreateArea(char *src,int size)
    {
        return new AreaPacket(src,size);
    }
    PacketBase *CreateVideoList(char *src,int size)
    {
        return new VideoListPacket(src,size);
    }

};


#endif // PACKETFACTORY_H
