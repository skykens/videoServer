#ifndef LISTENMEMTASK_H
#define LISTENMEMTASK_H
#include "../../ShmFIFO.h"
#include "../../Log/MallocLog.h"
#include "../../Epoll/EpollServer.h"
#include "TaskBase.h"
#include <sys/ipc.h>
#include <sys/types.h>

class ListenMemTask :public TaskBase//,protected MallocLog
{
public:
    ListenMemTask(unordered_map<int,TCPClient*>  &);
private:
    void run();
private:
    unordered_map<int,TCPClient*>  &clients;

};

#endif // LISTENMEMTASK_H
