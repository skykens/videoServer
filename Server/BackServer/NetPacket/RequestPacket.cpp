#include "RequestPacket.h"
RequestPacket::RequestPacket(char *arg)
{
    videoPacketEnd *end=(videoPacketEnd *)(arg+MAXPACKET-sizeof(videoPacketEnd));
    memcpy(m_packet,arg,sizeof(videoPacket));
    if(m_packet->head==PACKET_HEAD&&(*end)==PACKET_END)
    {
        body.body=(char *)malloc(m_packet->info.body_size);
        if(body.body==NULL)
        {
            perror("malloc error!");
            exit(1);
        }
        memcpy(body.body,arg+sizeof(videoPacket),m_packet->info.body_size);
        bodysize=m_packet->info.body_size;
        funcid=m_packet->info.funcid;
        isEffective=true;

    }
    else
    {
        printf("FIFOmem write error!\n");
        isEffective=false;
    }
}

RequestPacket::RequestPacket(videoPacket *data,struct packet_work *work,videoPacketEnd *end)
{
    memcpy(m_packet,data,sizeof(videoPacket));

    if(m_packet->head==PACKET_HEAD&&(*end==PACKET_END))
    {
        bodysize=m_packet->info.body_size;
        funcid=m_packet->info.funcid;
        isEffective=true;
        body.body=(char *)malloc(bodysize);
        if(body.body==NULL)
        {
            perror("body malloc error");
            exit(1);

        }
        memcpy(body.body,work->body,bodysize);
    }
    else
        isEffective=false;



}
RequestPacket::~RequestPacket()
{

}
 bool RequestPacket::toPacket()
 {
     int size=m_packet->info.body_size;
      if(m_packet->head!=0x0505)
        {
            m_packet->info.is_error=1;
            strcpy(m_packet->info.error_msg,"packet head error");
            isEffective=false;
            return false;
        }
//        if(m_packet->end!=0xffff)
//        {
//            m_packet->info.is_error=1;
//            strcpy(m_packet->info.error_msg,"packet end error");
//            isEffective=false;
//            return false;
//        }
        if(size!=sizeof(body.body))
        {
            m_packet->info.is_error=1;
            strcpy(m_packet->info.error_msg,"packet body size error");
            isEffective=false;
            return false;
        }
        //改进：可以加入校验码的检验
        isEffective=true;
        if(funcid=m_packet->info.funcid==T_keepActive)
            isActiveKeep=true;
        else
             isActiveKeep=false;


        return true;
 }
char * RequestPacket::Tochar ()
 {
    src=(char *)malloc(MAXPACKET);
    if(src==NULL)
    {
        perror("tochar malloc error!");
        exit(1);
    }
    videoPacketEnd end=PACKET_END;
    memcpy(src,m_packet,sizeof(videoPacket));
    if(body.body!=NULL)
        memcpy(src+sizeof(videoPacket),body.body,bodysize);
    else
    {
        printf("body=NULL! error!");
        free(src);
        src=NULL;
        return src;
    }
    memcpy(src+MAXPACKET-sizeof(videoPacketEnd),&end,sizeof(videoPacketEnd));

    return src;
 }
  videoPacket* RequestPacket::Getpacket()
 {
      return this->m_packet;

 }
