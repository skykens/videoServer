#include "PacketBase.h"
PacketBase::PacketBase(char *src,int size)
 :m_size(size)
{
   if(!init(src))
       throw "PacketBase src'malloc error";

}
PacketBase::PacketBase()
 :m_size(0),body(NULL)
{


}

void PacketBase::setBody(char *src,int size)
{
    m_size=size;
    if(body)
        free(body);
    if(!init(src))
        throw "malloc error";
}
bool PacketBase::init(char * src)
{

    char *tmp=(char *)malloc(m_size);
    if(!tmp)
        throw "malloc error";
    memcpy(tmp,src,m_size);
    head=(packet_head_t*)tmp;
    body=tmp+sizeof(packet_head_t);
    tail=(packet_tail_t* )(tmp+sizeof(packet_head_t)+head->packet_size);
    return true;

}


PacketBase::~PacketBase()
{
    if(body)
       free(body);
    body=NULL;

}


