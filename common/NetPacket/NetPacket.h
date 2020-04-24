#ifndef NETPACKET_H
#define NETPACKET_H
#include "PacketBase.h"
#include "CommonProto.pb.h"
using namespace NetWork;
namespace clientPacket{
class  login:public PacketBase
{
public:
    login():PacketBase(T_login,0){}
    virtual int getDataSize() const
    {
        return data.ByteSizeLong();
    }
    virtual bool getData(void * src) const
    {
        return data.SerializeToArray(src,data.ByteSizeLong());
    }
     ~login(){}
public:
    clientLogin data;
};

class  regist:public PacketBase
{
public:
    regist():PacketBase(T_register,0){}
    virtual int getDataSize() const
    {
        return data.ByteSizeLong();
    }
    virtual bool getData(void * src) const
    {
        return data.SerializeToArray(src,data.ByteSizeLong());
    }
    ~regist(){}
public:
    clientRegister data;
};

class  keepactive:public PacketBase
{
public:
    keepactive():PacketBase(T_keepActive,0){}
    virtual int getDataSize()  const
    {
        return 0;
    }
    virtual bool getData(void * src) const
    {
        return false;
    }
    ~keepactive(){}
public:
};

}

namespace serverPacket{

class  login:public PacketBase
{
public:
    login(int fd):PacketBase(T_login,fd){}
    virtual int getDataSize() const
    {
        return data.ByteSizeLong();
    }
    virtual bool getData(void * src) const
    {
        return data.SerializeToArray(src,data.ByteSizeLong());
    }
    ~login(){}
public:
    serverLogin data;
};

class  regist:public PacketBase
{
public:
    regist(int fd):PacketBase(T_register,fd){}
    virtual int getDataSize() const
    {
        return data.ByteSizeLong();
    }
    virtual bool getData(void * src) const
    {
        return data.SerializeToArray(src,data.ByteSizeLong());
    }
    ~regist(){}
public:
    serverRegister data;
};




}





#endif // NETPACKET_H
