#include "RelayPacket.h"
RelayPacket:: RelayPacket(char *arg)
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
        isEffective=true;
        client_fd=m_packet->info.client_fd;

    }
    else
    {
        printf("FIFOmem write error!\n");
        isEffective=false;
    }
}


RelayPacket::RelayPacket(int fd)
    :client_fd(fd)
{



}

RelayPacket::RelayPacket(videoPacket*data)
{

    memcpy(m_packet,data,sizeof(videoPacket));

}

void RelayPacket::Login(int userid,bool result)
{
    struct relay_login data;
    data.login_ret=result;
    data.user_id=userid;
    m_packet->head=0x0505;
    m_packet->info.body_size=sizeof(data);
    m_packet->info.client_fd=client_fd;
    m_packet->info.is_error=0;
    m_packet->info.seq=1;
    m_packet->info.sum=1;
    m_packet->info.trans_id=1;
    m_packet->info.funcid=T_login;
    if(body.body!=NULL)
        {
        printf("T_login clear body \n");
        free(body.body);
        printf("T_login clear end\n");
    }
    body.body=(char *)malloc(sizeof(struct relay_register));
    if(body.body==NULL)
    {
        perror("malloc error !");
        return ;
    }
    memcpy(body.body,&data,sizeof(data));
    Maxsize=sizeof(data);

}
void RelayPacket::Videolist(struct relay_videList *data,int i,int count)
{
    if(m_packet)
       free(m_packet);

    this->count=count;
    m_packet=(videoPacket*)malloc(sizeof(videoPacket));
    if(m_packet==NULL)
    {
        perror("malloc error !");
        return ;
    }
    memset(m_packet,0,sizeof(videoPacket));
    if(body.body!=NULL)
    {
        printf("videoPacket clear body \n");
        try{
            free(body.body);
        }catch(char * e)
        {
            printf("free body.body error!\n");
        }

        printf("videoPacket clear end\n");
    }
    body.body=(char *)malloc(sizeof(struct relay_videList));
    if(body.body==NULL)
    {
        perror("malloc error !");
        return ;
    }

        m_packet->head=0x0505;
        m_packet->info.body_size=sizeof(data);
        m_packet->info.client_fd=client_fd;
        m_packet->info.is_error=0;
        m_packet->info.seq=i+1;
        m_packet->info.sum=count;
        m_packet->info.trans_id=1;
        m_packet->info.funcid=T_requestList;
        memcpy(body.body,data,sizeof(struct relay_videList));
        Maxsize=sizeof(relay_videList)*count;
}

void RelayPacket::Regist(int userid,bool result)
{
    struct relay_register data;
    data.register_ret=result;
    data.user_id=userid;
    m_packet->head=0x0505;
    m_packet->info.body_size=sizeof(data);
    m_packet->info.client_fd=client_fd;
    m_packet->info.is_error=0;
    m_packet->info.seq=1;
    m_packet->info.sum=1;
    m_packet->info.trans_id=1;
    m_packet->info.funcid=T_register;
    if(body.body!=NULL)
        {
        printf("T_register clear body \n");
        free(body.body);
        printf("T_register clear end\n");
    }
    body.body=(char *)malloc(sizeof(struct relay_register));
    if(body.body==NULL)
    {
        perror("malloc error !");
        return ;
    }
    memcpy(&body,&data,sizeof(data));
    Maxsize=sizeof(data);
}



void RelayPacket::UploadHistory(bool result)
{
    struct relay_uploadHistory data;
    time_t now_time=time(NULL);
    tm*  t_tm = localtime(&now_time);
    srand((unsigned)time(NULL));
    int r1=rand()%10,r2=rand()%10,r3=rand()%10;
    data.result=result;
    sprintf(data.update_flowid,"%d%d%d%d%d%d%d%d%d%d",
            t_tm->tm_year,t_tm->tm_mon,t_tm->tm_mday,t_tm->tm_hour,t_tm->tm_min,t_tm->tm_sec,T_uploadHistory,r1,r2,r3);
    m_packet->head=0x0505;
    m_packet->info.body_size=sizeof(data);
    m_packet->info.client_fd=client_fd;
    m_packet->info.is_error=0;
    m_packet->info.seq=1;
    m_packet->info.sum=1;
    m_packet->info.trans_id=1;
    m_packet->info.funcid=T_uploadHistory;
    if(body.body!=NULL)
        {
        printf("T_uploadHistory clear body \n");
        free(body.body);
        printf("T_uploadHistory clear end\n");;
    }
    body.body=(char *)malloc(sizeof(struct relay_uploadHistory));
    if(body.body==NULL)
    {
        perror("malloc error !");
        return ;
    }
    memcpy(&(body),&data,sizeof(data));
    Maxsize=sizeof(data);
}


 char * RelayPacket::Tochar()
{
     src=(char *)malloc(MAXPACKET);
       if(src==NULL)
       {
           perror("tochar malloc error!");
           exit(1);
       }
       videoPacketEnd end=PACKET_END;
       memcpy(src,m_packet,sizeof(videoPacket));
      // body.body=(char *)malloc(m_packet->info.body_size);
       if(body.body==NULL)
      {
           perror("body  error!");
           exit(1);
       }

       memcpy(src+sizeof(videoPacket),body.body,m_packet->info.body_size);



       memcpy(src+MAXPACKET-sizeof(videoPacketEnd),&end,sizeof(videoPacketEnd));

       return src;



}
 videoPacket* RelayPacket::Getpacket()
{
    return  m_packet;
}

