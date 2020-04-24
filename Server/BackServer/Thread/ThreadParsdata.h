#ifndef THREADPARSDATA_H
#define THREADPARSDATA_H
#include "../ShmFIFO.h"
#include "M_Condition.h"
#include "safeQueue.hpp"
#include "ThreadBase.h"
#include "../../common/NetPacket/NetPacket.h"
#include "../sqlVideo/videoSqlite.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#define KEY_FIFO_SEND   ftok("/", 1)
#define KEY_FIFO_RECV   ftok("/", 2)

class ThreadParsdata :protected ThreadBase
{
public:
    ThreadParsdata(safeQueue<char *> &);
    virtual ~ThreadParsdata(){}
    void wakeUp();
    void start(){Thread_start(true);}
private:
    void run();
    void login();
    void registe();

private:
    videoSqlite *sql;
    char * buf_tmp;
    safeQueue<char *>  &buf_que;
    M_Condition cond;

};

#endif // THREADPARSDATA_H
