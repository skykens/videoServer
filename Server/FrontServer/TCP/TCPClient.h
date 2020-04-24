#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "TCPSocket.h"
#include "../Log/MallocLog.h"
#include "../Thread/M_Condition.h"
#include "../../common/NetPacket/NetPacket.h"
#include "../../common/NetPacket/public.h"
#define TIMENUM 3000
/** --------------派生类TCP Client ----------------**/
class TCPClient : public TCPSocket//,protected MallocLog
{
public:
    TCPClient(int clientfd);
    TCPClient(int clientfd, struct sockaddr_in *addr);
    void init();
    ~TCPClient();
    bool connect(unsigned short int port, const char *ip);
    char *GetHostIP();
    void ClrFD();
    int recvPacket();
    int sendPacket();
    int sendPacket(char * src,int size);
    inline void setDie()
    {
        printf("client=%d 已经断开连接 \n ",m_sockfd);
        signal.Lock();
        diebit=true;
        signal.unLock();
    }
    inline bool isDie(){return diebit;}
    inline void Timesub(){
        signal.Lock();
        if(timeKeep!=0)
                timeKeep--;
        signal.unLock();
    }
    inline bool isTimeout(){return !timeKeep;}
    inline void ClrTime()
    {
        signal.Lock();

        timeKeep=TIMENUM;
        signal.unLock();
    }
    inline int lock(){return signal.Lock();}
    inline const char *readBuf(){return buf;}
    inline int packet_size(){return packetsz;}
private:
    M_Condition signal;
    int timeKeep;
    bool diebit;
    char ipAddr[INET_ADDRSTRLEN];
    struct sockaddr_in svrAddr;
    char * buf;
    int packetsz;
    int Maxsize;

};

#endif // TCPCLIENT_H
