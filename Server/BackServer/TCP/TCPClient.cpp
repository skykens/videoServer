#include "TCPClient.h"
TCPClient::TCPClient(int clientfd)
    :TCPSocket(clientfd),timeKeep(TIMENUM),diebit(false),Maxsize(MAX_PACKET)
{
    try{
        init();
    }catch(const char * e)
    {
        writeError(string(e));
    }



}
void TCPClient::init()
{
    buf=(char *)malloc(Maxsize);
    if(!buf)
    {
        throw "TCPClient buf'malloc error";
        return ;
    }
    memset(buf,0,sizeof(Maxsize));
}

TCPClient::TCPClient(int clientfd, struct sockaddr_in *addr)
    :TCPSocket(clientfd),timeKeep(TIMENUM),diebit(false),Maxsize(MAX_PACKET)
{

    try{
        init();
    }catch(const char *e )
    {
        writeError(string(e));
    }

    memcpy(&svrAddr,addr,sizeof(sockaddr_in));

}
int TCPClient::recvPacket()
{

    int val=0;
   memset(buf,0,sizeof(Maxsize));
    packet_head_t *head;
    if((val=m_read((void *)buf,sizeof(packet_head_t)))<0)
    {
        string err(const_cast<char *>(strerror(errno)));
        memset(buf,0,sizeof(Maxsize));
        writeError("read head error :"+err);
        return -1;   //客户端出错  关闭客户端
    }
    if((head=(packet_head_t *)buf)->packet_head!=PACKET_HEAD)
    {
        memset(buf,0,sizeof(Maxsize));
        writeError("recvPacket'head error!");
        return -1;   //客户端出错  关闭客户端

    }
    packetsz=sizeof(packet_head_t);
    if((val=m_read((void *)(buf+packetsz),head->packet_size))<0)
    {
        string err(const_cast<char *>(strerror(errno)));
        memset(buf,0,sizeof(Maxsize));
        writeError("read body error :"+err);
        return -1;   //客户端出错  关闭客户端
    }
    packetsz+=head->packet_size;
    packet_tail_t  * tail;
    if(m_read((void *)(buf+packetsz),sizeof(packet_tail_t))<0)
    {
        string err(const_cast<char *>(strerror(errno)));

        memset(buf,0,sizeof(Maxsize));
        writeError("read tail error :"+err);
        return -1;   //客户端出错  关闭客户端
    }
    if((tail=(packet_tail_t*)(buf+packetsz))->packet_tail!= PACKET_END)
    {
        memset(buf,0,sizeof(Maxsize));
        writeError("recvPacket'tail error!");
        return -1;
    }
    packetsz+=sizeof(packet_tail_t);
    return packetsz;
}
int TCPClient::sendPacket()
{
    return m_write(buf,packetsz);
}
int TCPClient::sendPacket(char * src,int size)
{
    return m_write(src,size);

}
TCPClient::~TCPClient()
{
    if(buf)
        free(buf);

}
 int TCPClient::m_read(void *buf, int count)
{
    int val=0;
     signal.Lock();
    val= read(m_sockfd,buf,count);
         signal.unLock();
   return val;
}

 int TCPClient::m_write(const void *buf, int count)
{
     int val=0;
     signal.Lock();

     val= write(m_sockfd,buf,count);
     signal.unLock();
     return val;
}

void TCPClient::ClrFD()
{
    m_sockfd=0;
}
 char *TCPClient::GetHostIP()
{

     inet_ntop(AF_INET, &svrAddr.sin_addr, ipAddr, sizeof(ipAddr));
    return ipAddr;
}

