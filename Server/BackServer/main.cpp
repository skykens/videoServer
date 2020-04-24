/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年10月15日 星期二 22时40分48秒
 ************************************************************************/
#include "Epoll/BackServer.h"
#include "Thread/safeQueue.hpp"
#include "Thread/ThreadParsdata.h"
#include<iostream>
#include <sys/epoll.h>
#include <sys/types.h>
using namespace std;
int main(int argc,char *argv[])
{

#ifdef BACKSERVER
    safeQueue<char *> buf;
    BackServer backServer(10,buf);
    backServer.start();

    while(buf.size())
    {
        char * tmp=buf.front();
        buf.pop();
        free(tmp);
    }


#endif
#ifdef FRONTSERVER
    EpollServer *frontServer=new EpollServer(num,EPOLLIN|EPOLLET,port,377924);
    printf("前置服务器启动\n");
    frontServer->Start();
#endif



 return 0;
}
