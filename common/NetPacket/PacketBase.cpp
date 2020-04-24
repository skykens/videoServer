#include "PacketBase.h"
PacketBase::PacketBase(int funcid,int fd)
{
    head.func_id=funcid;
    head.fd=fd;
    head.packet_head=PACKET_HEAD;
    head.error_code=0;
    head.error_msg[0]='\0';
    head.optid=0;
    head.crc=0;
    head.packet_seq=1;
    head.packet_sum=1;
    tail.packet_tail=PACKET_END;

}
void PacketBase::setCliend(int fd)
{
    head.fd=fd;
}
int PacketBase::SerializeToArray(void *data,int size)
{
    int datasize=getDataSize();
    if(size<sizeof(head)+datasize+sizeof(tail))
        return -1;
    head.packet_size=getDataSize();
    memcpy(data,&head,sizeof(head));
    if(getDataSize())
       getData(data+sizeof(head));
    memcpy(data+sizeof(head)+getDataSize(),&tail,sizeof(tail));
    return sizeof(head)+datasize+sizeof(tail);
}
PacketBase::~PacketBase()
{
}


