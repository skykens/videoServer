#define FRONTSERVER
#ifndef EPOLLSERVER_H
#define EPOLLSERVER_H
#include "EpollBase.h"
#include "../Thread/ThreadPool.h"
#include "../Thread/ThreadBase.h"
#include "../Thread/Task/ClientTask.h"
#include "../Thread/Task/ListenClientTask.h"
#include "../Thread/Task/ListenMemTask.h"
#include "../Log/EpollLog.h"
#include <vector>
#include<algorithm>
#include <sys/ipc.h>
#include <sys/types.h>

class EpollServer:public EpollBase ,public ThreadBase
{
public:
    EpollServer(int maxThread,int set_event,int port,unsigned int maxEvent = 377924,const char * ip=NULL, int timeout = -1);
    inline TCPServer *GetServer(){return server;}
    inline int Getdefevent(){return defevent;}
    inline  void Start(){m_bStop=false;Thread_start(true);}
    TCPClient *findClientFd(int fd);
    ~EpollServer(){}
private:
    EpollLog *log;
    M_Condition signal;
    ThreadPool *threadPool;
    TCPServer *server;
    int defevent;  //默认新客户端进来默认创建的监听事件
    std::vector<TCPClient*> clients;
private:
     void run();  //主线程
};

#endif // EPOLLSERVER_H
