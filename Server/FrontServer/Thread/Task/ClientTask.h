#ifndef CLIENTTASK_H
#define CLIENTTASK_H
#include "TaskBase.h"
#include "../../Epoll/EpollServer.h"
#include "../../TCP/TCPServer.h"
#include "../../TCP/TCPClient.h"
#include "../../ShmFIFO.h"
#include "../../Log/TaskLog.h"
#include "../../coreGui.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include "../../Log/MallocLog.h"
#define KEY_FIFO_RECV   ftok("/", 2)
using namespace std;
class EpollServer;
class ClientTask :public TaskBase//,protected MallocLog
{
public:
    ClientTask(TCPClient &,EpollServer *base);
private:
    void run();
private:
    TCPClient &client;
    EpollServer &base;
};

#endif // CLIENTTASK_H
