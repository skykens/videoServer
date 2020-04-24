#define FRONTSERVER
#ifndef EPOLLSERVER_H
#define EPOLLSERVER_H
#include "EpollBase.h"
#include "../TCP/TCPServer.h"
#include "../TCP/TCPClient.h"
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
#include "../../common/NetPacket/Config.h"
#include "../coreGui.h"
class ThreadPool;
using namespace std;
class EpollServer:public EpollBase
{
public:
    EpollServer(int maxThread,int defThread,int set_event,int port,unsigned int maxEvent = 377924,const char * ip=NULL, int timeout = -1);
    inline TCPServer *GetServer(){return server;}
    inline int Getdefevent(){return defevent;}
    inline  void Start(){while(1){run();}}
    void removeClient(int fd);
    //TCPClient *findClientFd(int fd);
    ~EpollServer(){}
private:

    int event_count;  //唤醒次数
    EpollLog *log;
    ThreadPool *threadPool;
    TCPServer *server;
    int defevent;  //默认新客户端进来默认创建的监听事件
    unordered_map<int,TCPClient*> clients;
public:
     void run();  //主线程
};

#endif // EPOLLSERVER_H
