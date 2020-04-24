/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年10月15日 星期二 22时40分48秒
 ************************************************************************/
#include "Epoll/EpollServer.h"
#include "../../common/NetPacket/Config.h"
#include "coreGui.h"
#include<iostream>
#include <sys/epoll.h>
#include <sys/types.h>
using namespace std;
int main(int argc,char *argv[])
{
#ifdef BACKSERVER

    BackServer *backServer=new BackServer(377924);
    backServer->Start();
#endif
#ifdef FRONTSERVER
    Config* sys=Config::ConfigInit();
    EpollServer *frontServer=new EpollServer(sys->max_threads,sys->default_threads,EPOLLIN|EPOLLONESHOT,sys->port,sys->max_listens);


    //  printf("前置服务器启动\n");

#endif


    frontServer->Start();


 return 0;
}
