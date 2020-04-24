#ifndef COREGUI_H
#define COREGUI_H

#include <stdio.h>
#include <iostream>
#include "Thread/M_Condition.h"
#include "Thread/ThreadBase.h"
#include <unordered_map>
using namespace std;
class coreGui :public ThreadBase
{
public:
    virtual void run();
    static void initGui();
    void pEpollstatus();
    void pPoolstatus();
    void pClientStatus();
    void pMemStatus();
    void pFDStatus();
    void pComeEvent();
   static void  clrScreen();
   static  void wComeEvent(int n);
   static  void wListenFd(int fd);
   static  void wEpollstatus(int maxE,int curE,int countW);
   static  void wPoolstatus(int maxTh,int workTh,int curTh,int waitTa);
   static  void wClientStatus(int count);
   static  void wMemStatus(int count,int err);
   ~coreGui(){}
private:
   coreGui();
public:
   static coreGui * core;
private:
   int nfds_event=0;
   unordered_map<int,int> fds;
   int memErrCount=0;
   int memCount=0;
   int packetCount=0;
   int maxEvent=0;
   int curEvent=0;
   int countWake=0;
   int maxThreads=0;
   int workThreads=0;
   int curThreads=0;
   int waitTask=0;
};

#endif // COREGUI_H
