#include "HostAddress.h"
CHostAddress::CHostAddress(const char *ip, unsigned short port)
{
    memset(&m_addr,0,sizeof(m_addr));
    this->m_length = sizeof(m_addr);
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    if(ip == NULL)
    {
        m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        m_addr.sin_addr.s_addr = inet_addr(ip);
    }
}

CHostAddress::CHostAddress()
{
    memset(&m_addr,0,sizeof(m_addr));
    this->m_length = sizeof(m_addr);
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

CHostAddress::~CHostAddress()
{

}

void  CHostAddress::SetIp(const char *ip)
{
    if(ip == NULL)
    {
        m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        m_addr.sin_addr.s_addr = inet_addr(ip);
    }
}

const char* CHostAddress::GetIp()
{
    return inet_ntoa(m_addr.sin_addr);
}

void CHostAddress::SetPort(unsigned short port)
{
    m_addr.sin_port = htons(port);
}

unsigned short CHostAddress::GetPort()
{
    return ntohs(m_addr.sin_port);
}

struct sockaddr * CHostAddress::Address()
{
    return (struct sockaddr *)&m_addr;
}

struct sockaddr_in * CHostAddress::InAddress()
{
    return &m_addr;
}

int CHostAddress::Length()
{
    return m_length;
}

socklen_t* CHostAddress::LengthPtr()
{
    return (socklen_t *)&m_length;
}



