#ifndef RELAYPACKET_H
#define RELAYPACKET_H
#include "PacketBase.h"

//应答包的生成
class RelayPacket:public PacketBase
{
public:
    RelayPacket(char *);
    RelayPacket(videoPacket*);
    RelayPacket(int fd);
    //创建不同类型数据包
  void Login(int userid,bool result);
  void Regist(int userid,bool result);
  void Videolist(struct relay_videList *data,int i,int count);
  //count：结构体元素个数
  void UploadHistory(bool result);
    virtual char * Tochar();
    virtual videoPacket* Getpacket();

private:

  bool isEffective;
  int client_fd;

};

#endif // RELAYPACKET_H
