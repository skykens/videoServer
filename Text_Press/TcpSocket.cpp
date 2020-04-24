#include "TcpSocket.h"

CTcpSocket::CTcpSocket(void)
{
    Create();
}
CTcpSocket::CTcpSocket(const CTcpSocket &other)
{
    CBaseSocket::SetSocket(other.GetSocket());
    SetRemoteAddr(other.GetRemoteAddr());
}

CTcpSocket::CTcpSocket(int fd)
{
    CBaseSocket::SetSocket(fd);
}

CTcpSocket::~CTcpSocket(void)
{
}

CTcpSocket & CTcpSocket::operator= (const CTcpSocket &other)
{
    CBaseSocket::SetSocket(other.GetSocket());
    SetRemoteAddr(other.GetRemoteAddr());
    return *this;
}

CHostAddress CTcpSocket::GetRemoteAddr() const
{
    //return m_remote_addr;
    CHostAddress addr;
    memset(&addr,0,sizeof(addr));
    if(getpeername(m_fd,addr.Address(),addr.LengthPtr()) != 0)
    {
        perror("getpeername");
    }
    return addr;
}
void CTcpSocket::SetRemoteAddr(const CHostAddress remote_addr)
{
    this->m_remote_addr = remote_addr;
}

bool CTcpSocket::Connect(CHostAddress addr)
{
    if ( ::connect(m_fd,addr.Address(),addr.Length()) == -1)
    {
        perror("connect");
        return false;
    }
    SetRemoteAddr(addr);
    return true;
}

int CTcpSocket::Read(char *buf, const int buf_len)
{
    return m_stream.Read(buf,buf_len);
}

int CTcpSocket::Readn(char *buf, const int buf_len)
{
    return m_stream.Read(buf,buf_len);
}

int CTcpSocket::recvn(char *buf, int count)
{
    return m_stream.Recv(buf,count);
}

int CTcpSocket::Write(char *buf, const int buf_len)
{
    return m_stream.Write(buf,buf_len);
}

void CTcpSocket::Create()
{
    CBaseSocket::Create(AF_INET,SOCK_STREAM,0);
}
