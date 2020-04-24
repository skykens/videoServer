#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
/*---------------TCP基类----------------*/
class TCPSocket
{
public:
    TCPSocket(int fd);
    TCPSocket();
    virtual ~TCPSocket();
    bool create(void);
    bool reuseaddr(void);    //地址重复使用
    bool setNonBlocking(); 
    bool setNonBlocking(int fd, bool flag);  //flag: true=SetNonBlock, false=SetBlock;
    inline int  getfd(){return m_sockfd;}
    bool isValid();
    bool m_close();

    // 基类正常没有读取操作，根据派生类重载
    virtual int m_read(void *buf, int count);
    virtual int m_write(const void *buf, int count);
    virtual int m_readn(int fd, void *buf, int count);
    virtual int m_writen(int fd, const void *buf, int count);
    //int send(Packet * pack);
    //int receive(Packet * pack);

protected:
    int m_sockfd;
    struct sockaddr_in m_svrAddr;
    struct sockaddr_in m_cliAddr; //连接的客户端信息
};

#endif // TCPSOCKET_H
