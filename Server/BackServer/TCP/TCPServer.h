#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "TCPSocket.h"
#define DEFAULT_PORT 6666
class TCPServer : public TCPSocket
{
public:
    TCPServer(int listeNum,unsigned short int port=DEFAULT_PORT, const char *ip = NULL);
    bool m_bind();
    bool m_listen();
    int m_accept();  //创建客户端连接
    inline struct sockaddr_in* GetSockaddr(){return &client_addr;}  //返回客户端信息
    ~TCPServer();

private:
    const char *m_ip;
    unsigned short int m_port;
    int ListenNum;
    struct sockaddr_in client_addr;
    socklen_t addrlen;


//public slots:
};

#endif // TCPSERVER_H
