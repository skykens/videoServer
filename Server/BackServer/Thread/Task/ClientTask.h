#ifndef CLIENTTASK_H
#define CLIENTTASK_H
#include "TaskBase.h"
#include "../../TCP/TCPServer.h"
#include "../../TCP/TCPClient.h"
#include "../../ShmFIFO.h"
#include "../../Log/TaskLog.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#define KEY_FIFO_RECV   ftok("/", 2)
using namespace std;
class ClientTask :public TaskBase
{
public:
    ClientTask(TCPClient &);
private:
    void run();
private:
    TaskLog *log;
    TCPClient &client;
};

#endif // CLIENTTASK_H
