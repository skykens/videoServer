#ifndef PARSDATATASK_H
#define PARSDATATASK_H
#include "../../ShmFIFO.h"
#include "../../TCP/TCPPacket.h"
#include "TaskBase.h"
#include "../../sqlVideo/videoSqlite.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define KEY_FIFO_SEND   ftok("/", 1)
#define KEY_FIFO_RECV   ftok("/", 2)

class ParsDataTask :public TaskBase
{
public:
    ParsDataTask(RequestPacket *);
private:
    void run();
    static int SendList(void *data, int argc, char **argv, char **azColName);
private :
    RequestPacket *packet;
};

#endif // PARSDATATASK_H
