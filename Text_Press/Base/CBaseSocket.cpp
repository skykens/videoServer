#include "CBaseSocket.h"
#include <iostream>
using namespace std;

CBaseSocket::CBaseSocket()
{
    this->m_fd = -1;
    this->m_stream.SetFd(m_fd);
}

CBaseSocket::CBaseSocket(int type, int sin_farmly , int protocol )
{
    Create(sin_farmly,type,protocol);
}

CBaseSocket::~CBaseSocket()
{

}

void CBaseSocket::SetSocket(int fd)
{
    this->m_fd = fd;
    m_stream.SetFd(m_fd);
}

CHostAddress CBaseSocket::GetAddress()
{
    CHostAddress addr;
    if(getsockname(m_fd,addr.Address(),addr.LengthPtr()) != 0)
    {
        perror("error addr\n");
    }
    return addr;
}

CHostAddress CBaseSocket::GetPeerAddress()
{
    CHostAddress addr;
    if(getpeername(m_fd,addr.Address(),addr.LengthPtr()) != 0)
    {
        perror("Peeraddr error\n");
    }
    return addr;
}

bool CBaseSocket::Bind(CHostAddress hostaddr)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(hostaddr.GetIp());
    addr.sin_port = htons(hostaddr.GetPort());

    int r = bind(m_fd, (struct sockaddr *)&addr, sizeof(addr));
    if(r == -1)
            perror("bind error\n");

    return r;
}

bool CBaseSocket::Close()
{
    if(this->m_fd == -1)
    {
        printf("m_fd ivalid \n");
        return false;
    }
    int res = close(m_fd);
    if(res < 0)
    {
        return false;
    }
    return true;
}

void CBaseSocket::Create(int sin_farmly,int flag,int protocl)
{
    if(m_fd < 0)
    {
        this->m_fd = ::socket(sin_farmly, flag, protocl);
        if (m_fd == -1)
        {
            perror("socket error\n");
        }
        m_stream.SetFd(m_fd);
        int on = 1;
        if(setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        {
            perror("setsockopt error\n");
        }
    }
}
