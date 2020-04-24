#include "TCPPacket.h"
TCPPacket::TCPPacket(RelayPacket *packet)
{
    Relay=packet;
    client=new TCPClient(Relay->Getpacket()->info.client_fd);
}
TCPPacket::TCPPacket(TCPClient * i)
{
    client=i;
    Relay=NULL;
    Request=NULL;
}
TCPPacket::TCPPacket(videoPacket*data)
{

        Relay=new RelayPacket(data);
        client=new TCPClient(data->info.client_fd);







}

TCPPacket::~TCPPacket()
{
    if(!Relay)
        delete Relay;
    if(!Request)
        delete Request;
    if(!client)
        {
        client->ClrFD();
        delete client;
    }


}
int TCPPacket::recvPacket()
{

    int val;
    char* buf=(char *)malloc(sizeof(videoPacket));
    if(buf==NULL)
    {
        perror("recv_head malloc error!");
        return -2;
    }
    memset(buf,0,sizeof(videoPacket));
    val=client->m_read((void *)buf,sizeof(videoPacket));
    if(val==0&&(*buf)==0)
    {
        free(buf);
        return -1;   //客户端 关闭
    }
    videoPacket *test=(videoPacket*)buf;
    packet_work *body=(packet_work *)malloc(sizeof(packet_work ));
    test->info.client_fd=client->getfd();
    body->body=(char *)malloc(test->info.body_size);
    if(body->body==NULL)
    {
        perror("recv_head malloc error!");
        return -2;
    }
    val=client->m_read((void *)body->body,test->info.body_size);
    if(val<0)
    {
        printf("客户端出错\n");
        free(buf);
        free(body->body);
        return -1;   //客户端出错  关闭客户端
    }
    videoPacketEnd end;
    val=client->m_read((void *)&end,sizeof(videoPacketEnd));
    if(val<0||end==0)
    {
        free(buf);
        free(body->body);
        return -3;   //客户端发包出错
    }
    Request=new RequestPacket(test,body,&end);
    free(buf);
    free(body->body);
    return 0;
}
int TCPPacket::sendPacket()
{
    if(Relay==NULL)
    {
        printf("send Packet error!Relay=NULL\n");
        return -1;
    }
    if(client->m_write(Relay->Getpacket(),sizeof(videoPacket))<0)
    {
        printf("write error!\n");
        return -1;
    }
    if(client->m_write(Relay->Getwork()->body,Relay->Getpacket()->info.body_size)<0)
    {
        printf("write error!\n");
        return -1;
    }
    videoPacketEnd end=PACKET_END;
    if(client->m_write(&end,sizeof(videoPacketEnd))<0)
    {
        printf("write error!\n");
        return -1;
    }
    return 0;

}

int TCPPacket::writeRelay(RelayPacket*data)
{
    Relay=data;
    return 0;
}
int TCPPacket::writeRelay(RelayPacket data)
{
    Relay=new RelayPacket(data);
    return 0;
}
