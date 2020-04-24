#include "TCPSocket.h"
TCPSocket::TCPSocket(int fd)
{
    m_sockfd=fd;
}

TCPSocket::TCPSocket()
{
    if(!create())
    {
        perror("create error!");
        exit(1);

    }
}


bool TCPSocket::create(void)
{
    int on;
    if((m_sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket create error!");
        return false;
    }
    if(setsockopt(m_sockfd,SOL_SOCKET,SO_REUSEADDR,(void *)&on,sizeof(on))<0)
    {
        perror("Failed to set socket");
        return false;


    }

    return true;
}


bool TCPSocket::reuseaddr(void)    //地址重复使用
{


}
bool TCPSocket::setNonBlocking()  //flag: true=SetNonBlock, false=SetBlock;
{
 int old_flags = fcntl(m_sockfd, F_GETFL);
   if(fcntl(m_sockfd, F_SETFL, old_flags | O_NONBLOCK)<0)
     return false;
 return true;
}

bool TCPSocket::setNonBlocking(int fd, bool flag)  //flag: true=SetNonBlock, false=SetBlock;
{



}

bool TCPSocket::isValid()
{

}
bool TCPSocket::m_close()
{
    if(m_sockfd<3)
    {
        return true;
    }
    if(close(m_sockfd)<0)
     {
        perror("close m_sockfd error!");
        return false;
    }else
        {
        return true;
    }
}


//读写操作（虚函数）

 int TCPSocket::m_read(void *buf, int count)
{

    return m_readn(m_sockfd,buf,count);

}

 int TCPSocket::m_write(const void *buf, int count)
{



    return m_writen(m_sockfd,buf,count);
}

 int TCPSocket::m_readn(int fd, void *buf, int count)
{
     int val=0;
     if(m_sockfd<0)
     {
         throw "read m_sockfd error ! ";
         return -1;
     }
     if((val=read(fd,buf,count))<0&&errno==EINTR)
         return read(fd,buf,count);
     return val;


}

 int TCPSocket::m_writen(int fd, const void *buf, int count)
{
     int val=0;
     if(m_sockfd<0)
     {
         throw "wirte m_sockfd error ! ";
         return -1;
     }
     if((val=write(fd,buf,count))<0&&errno==EINTR)
         return write(fd,buf,count);
     return val;




}
TCPSocket::~TCPSocket()
 {
        m_close();
 }
