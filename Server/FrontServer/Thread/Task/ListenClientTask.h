#ifndef LISTENCLIENTTASK_H
#define LISTENCLIENTTASK_H
#include "TaskBase.h"
#include "../../TCP/TCPClient.h"
#include "../../Thread/M_Condition.h"
#include "../../Epoll/EpollBase.h"
#include <sys/ipc.h>
#include <sys/types.h>
#include <unordered_map>
using namespace std;
class ListenClientTask :public TaskBase
{
public:
    ListenClientTask(unordered_map<int,TCPClient*> &source,M_Condition *clientMutex,EpollBase *server);
    virtual  ~ListenClientTask(){}
private:
    void run();
private:
    EpollBase * Epoll;
    M_Condition *signal;
    unordered_map<int,TCPClient*>  &clients;
};

#endif // LISTENCLIENTTASK_H
