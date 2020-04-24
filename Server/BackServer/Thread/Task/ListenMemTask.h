#ifndef LISTENMEMTASK_H
#define LISTENMEMTASK_H
#include "../../ShmFIFO.h"
#include "../../Log/TaskLog.h"
#include "../../Epoll/EpollServer.h"
#include "TaskBase.h"
#include <sys/ipc.h>
#include <sys/types.h>

class ListenMemTask :public TaskBase
{
public:
    ListenMemTask();
private:
    void run();
private:
    TaskLog * log;
};

#endif // LISTENMEMTASK_H
