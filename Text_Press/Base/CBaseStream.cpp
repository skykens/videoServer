#include "CBaseStream.h"

CBaseStream::CBaseStream()
{
    this->m_fd = -1;
}

CBaseStream::CBaseStream(int fd)//普通构造
{
    this->m_fd = fd;
}

CBaseStream::~CBaseStream(void)
{

}

void CBaseStream::SetFd(int fd)
{
    this->m_fd = fd;
}

int CBaseStream::GetFd() const
{
    return m_fd;
}
int CBaseStream::Read(char *buf, const int buf_len)
{
    if(m_fd == -1)
    {
        printf("m_fd无效\n");
        return -1;
    }
    int ret = read(m_fd,buf,buf_len);
    if(ret == -1)
    {
        perror("read");
    }
    return ret;
}

int CBaseStream::Readn(char *buf, const int buf_len)
{
    int nLeft = buf_len;//剩下多少要读
     int nRead = 0;
     while (nLeft > 0)
     {
         nRead = read(m_fd,buf,buf_len);
         if (nRead < 0)
         {
             if (errno == EINTR)  //如果读取操作是被信号打断了, 则说明还可以继续读
             {
                 printf("continue read\n");
                 continue;
             }
             else
                 return -1;
         }
         else if (nRead == 0)     //对方关闭连接
         {
             printf("read == 0\n");
             return -1;
         }
         else  //正常读取
         {
             nLeft -= nRead;
             buf += nRead;
         }
     }
     return buf_len;
}

int CBaseStream::Recv(char *buf, const int buf_len)
{
    if(m_fd == -1)
    {
        printf("m_fd无效\n");
        return -1;
    }
    int nLeft = buf_len;//剩下多少要读
    int nRead = 0;
    while(nLeft>0)
    {
        nRead = recv(m_fd,buf,buf_len,MSG_WAITALL);//MSG_WAITALL
        if(nRead == -1)
        {
            if (errno == EINTR)  //如果读取操作是被信号打断了, 则说明还可以继续读
            {
                printf("continue recv\n");
                continue;
            }
            else if(errno == EWOULDBLOCK || errno == EAGAIN)            //否则就是其他错误
            {
                printf("timeout\n");
                return -1;
            }
        }
        else if (nRead == 0)     //对方关闭连接
        {
            printf(" recv == 0\n");
            return -1;
        }
        else  //正常读取
        {
            nLeft -= nRead;
            buf += nRead;
        }
    }
    return buf_len;
}

int CBaseStream::Write(const char *buf, const int buf_len)
{
    if(m_fd == -1)
    {
        printf("m_fd无效\n");
        return -1;
    }
    int ret = write(m_fd,buf,buf_len);
    if(ret == -1)
    {
        perror("write\n");
    }
    return ret;
}
