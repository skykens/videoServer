#include "TCPServer.h"

TCPServer::TCPServer(int listeNum,unsigned short int port, const char *ip )
    :TCPSocket(),ListenNum(listeNum),m_ip(ip),m_port(port)
{
    if(!m_bind())
    {
        perror("bind error");
        exit(EXIT_FAILURE);
    }
    if(!m_listen())
    {
        perror("listen error");
        exit(EXIT_FAILURE);
    }

}


bool TCPServer::m_bind()
{
    bzero(&m_svrAddr,sizeof(m_svrAddr));
    m_svrAddr.sin_family=AF_INET;
    if(m_ip==NULL)
    {
        
        m_svrAddr.sin_addr.s_addr=htonl(INADDR_ANY);

    }
    else
    {
        printf("这个地方还没写，不知道怎么绑定具体IP（On m_bind)");
        exit(1);
       // m_svrAddr.sin_addr.s_addr=htonl( ip);

    }
    m_svrAddr.sin_port=htons(m_port);
    if(bind(m_sockfd,(struct sockaddr *)&m_svrAddr,sizeof(m_svrAddr))<0)
        return false;
    return true;
}


bool TCPServer::m_listen( )
{
    if(listen(this->getfd(),ListenNum)<0)
        return false;
    return true;


}



int TCPServer::m_accept()  //创建客户端连接
{

    return  accept(this->getfd(), (struct sockaddr*)&client_addr,&addrlen);

}
TCPServer::~TCPServer()
{
}
