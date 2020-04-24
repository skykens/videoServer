#ifndef FACTORY_H
#define FACTORY_H
#include "PacketBase.h"
// 总厂
class Factory
{
public:
    Factory();
   virtual PacketBase *CreateLogin(char *src,int size)=0;
   virtual  PacketBase *CreateRegis(char *src,int size)=0;
   virtual  PacketBase *CreateKeepActive(char *src,int size)=0;
   virtual  PacketBase *CreateClass(char *src,int size)=0;
   virtual  PacketBase *CreateVideoType(char *src,int size)=0;
   virtual  PacketBase *CreateArea(char *src,int size)=0;
   virtual  PacketBase *CreateVideoList(char *src,int size)=0;

    virtual ~Factory() {}
};


#endif // FACTORY_H
