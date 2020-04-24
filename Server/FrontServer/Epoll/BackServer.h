/*************************************************************************
	> File Name: BackServer.h
	> Author: 
	> Mail: 
	> Created Time: 2019年10月27日 星期日 10时57分20秒
 ************************************************************************/
#define BACKSERVER
#ifndef _BACKSERVER_H
#define _BACKSERVER_H
#include "EpollBase.h"
#include "../TCP/TCPPacket.h"
#include "../Thread/ThreadPool.h"
#include "../NetPacket/RequestPacket.h"
#include "../NetPacket/RelayPacket.h"
#include "../Thread/ThreadBase.h"
#include "../Thread/Task/ParsDataTask.h"
#include "../ShmFIFO.h"
#include "../sqlVideo/videoSqlite.h"
#include <vector>
#include<algorithm>
#include <time.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define KEY_FIFO_SEND   ftok("/", 1)
#define KEY_FIFO_RECV   ftok("/", 2)

class BackServer:public EpollBase,public ThreadBase
{
public:
    BackServer(int maxThread);
    inline virtual void Start(){m_bStop=false;Thread_start(true);}
    ~BackServer();

private:
    M_Condition signal;
    ThreadPool *threadPool;
private:
    void run();
private:
    unsigned long login_count;
    unsigned long getlist_count;
    unsigned long getHistory_count;
    unsigned long uploadHistory_count;
    unsigned long uploadHour_count;


};







#endif
