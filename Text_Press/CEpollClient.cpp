#include "CEpollClient.h"

CEpollClient::CEpollClient(int sum,CHostAddress myaddr,unsigned int maxEvent,int timeout)
    :CEpollBase(maxEvent,timeout)
{
    addr=myaddr;
    this->ClientSum=sum;
    connectSucces=0;
    this->RecvSum=0;
    RecvSumFail=0;
    heart=new clientPacket::keepactive();
}
void CEpollClient::startNewConnect()
{
    OnNewConnection();
}

void CEpollClient::OnNewConnection()
{
    for(int i=0;i<ClientSum;i++)
    {
        CTcpSocket *myClient=new CTcpSocket;
        if(myClient->Connect(addr))
        {
            AddEvent(myClient->GetSocket(),EPOLLIN|EPOLLET);
            //write(myClient->GetSocket(),heart->getData(),1024);  先发送心跳包
            client_fd.insert(myClient->GetSocket());
            connectSucces++;
        }
    }
    qDebug()<<connectSucces;
}

CEpollClient::~CEpollClient()
{
    for(int i: client_fd)
    {
        OnClientClose(i);
    }
    SetTimeout(0);
    Stop();
}

void CEpollClient::OnReadData(int fd)
{

    int val=0;
    char buf[1024];
    packet_head_t *head;
    RecvSum++;
    if((val=read(fd,(void *)buf,sizeof(packet_head_t)))<0)
    {
        string err(const_cast<char *>(strerror(errno)));
        cout<<err;
        OnClientClose(fd);
        RecvSumFail++;
        return ;
    }
    if((head=(packet_head_t *)buf)->packet_head!=PACKET_HEAD)
    {
            RecvSumFail++;
            return ;

    }
    int packetsz=sizeof(packet_head_t);
    if((val=read(fd,(void *)(buf+packetsz),head->packet_size))!=head->packet_size)
    {
        string err(const_cast<char *>(strerror(errno)));
        cout<<err;
        OnClientClose(fd);
        RecvSumFail++;
        return ;
    }
    packetsz+=head->packet_size;
    packet_tail_t  * tail;
    if(read(fd,(void *)(buf+packetsz),sizeof(packet_tail_t))<0)
    {
        string err(const_cast<char *>(strerror(errno)));
        cout<<err;
        OnClientClose(fd);
        RecvSumFail++;
        return ;

    }
    if((tail=(packet_tail_t*)(buf+packetsz))->packet_tail!= PACKET_END)
    {
            RecvSumFail++;
    }



}

void CEpollClient::OnClientClose(int fd)
{
//    DelEvent(fd,EPOLLIN);
//    connectSucces--;
//    client_fd.erase(fd);
//    close(fd);
}

void CEpollClient::Run(int nevent)
{
    for (int i = 0; i < nevent;i++)
    {
        if ((m_retEvent + i)->events & EPOLLIN)
        {
            OnReadData((m_retEvent + i)->data.fd);
        }
    }
}
