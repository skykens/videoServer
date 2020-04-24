#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "Base/CBaseSocket.h"
#include "Base/HostAddress.h"

class CTcpSocket :public CBaseSocket
{
public:
    CTcpSocket(void);
    CTcpSocket(const CTcpSocket &other);
    CTcpSocket(int fd);
    ~CTcpSocket(void);
    CTcpSocket & operator= (const CTcpSocket &other);
    CHostAddress GetRemoteAddr() const; //获取服务器地址信息
    void SetRemoteAddr(const CHostAddress remote_addr); //设置服务器地址信息
    bool Connect(CHostAddress addr);
    int Read(char *buf, const int buf_len);
    int Readn(char *buf, const int buf_len);
    int recvn(char *buf, int count);
    //int Read(char *buf, const int buf_len, struct timeval *tv);
    int Write(char *buf, const int buf_len);
    //int Write(char *buf, const int buf_len, struct timeval *tv);
protected:
    void Create();
    CHostAddress m_remote_addr; //服务器地址信息
};

#endif // TCPSOCKET_H
