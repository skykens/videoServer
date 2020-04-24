#ifndef PACKETFACTORY_H
#define PACKETFACTORY_H
#include "Factory.h"
#include "PacketBase.h"
#include "NetPacket.h"

class PacketFactory : public Factory
{
public:
     PacketFactory();
    PacketBase *CreateLogin()
    {
        return new LoginPacket();
    }
    PacketBase *CreateRegis()
    {
        return new RegisPacket();
    }
    PacketBase *CreateKeepActive()
    {
        return new KeepActivePacket();
    }
    PacketBase *CreateClass()
    {
        return new ClassPacket();
    }
    PacketBase *CreateVideoType()
    {
        return new VideoTypePacket();
    }
    PacketBase *CreateArea()
    {
        return new AreaPacket();
    }
    PacketBase *CreateVideoList()
    {
        return new VideoListPacket();
    }

};


#endif // PACKETFACTORY_H
