#ifndef FACTORY_H
#define FACTORY_H
#include "PacketBase.h"
// 总厂
class Factory
{
public:
   Factory();
   virtual  PacketBase *CreateLogin()=0;
   virtual  PacketBase *CreateRegis()=0;
   virtual  PacketBase *CreateKeepActive()=0;
   virtual  PacketBase *CreateClass()=0;
   virtual  PacketBase *CreateVideoType()=0;
   virtual  PacketBase *CreateArea()=0;
   virtual  PacketBase *CreateVideoList()=0;

    virtual ~Factory() {}
};


#endif // FACTORY_H
