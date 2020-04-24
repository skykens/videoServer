#include "PacketBase.h"
PacketBase::PacketBase()
{
    Maxsize=sizeof(videoPacket);
    m_packet=(videoPacket*)malloc(sizeof(videoPacket));
    if(!m_packet)
     {
        perror("malloc error!");
        exit(1);
    }
    memset(m_packet,0,sizeof(videoPacket));

}

int PacketBase::writeError(const char *errmsg)
{
    src=NULL;
    if(m_packet==NULL)
    {

        printf("writeError error!\n");
        return -1;
    }
    m_packet->head=PACKET_HEAD;
    strcpy(m_packet->info.error_msg,errmsg);
    m_packet->info.is_error=true;
     return 0;
}

PacketBase::~PacketBase()
{
    if(body.body!=NULL)
        free(body.body);
    if(m_packet!=NULL)
          free(m_packet);

}


