#include "coreGui.h"
coreGui * coreGui::core =NULL;
coreGui::coreGui()
{

}
void coreGui::initGui()
{
    if(!core)
        core=new coreGui();
    core->Thread_start(true);
}
void coreGui::coreGui::run()
{
   // printf("\033[2J"); //clear
    pEpollstatus();
    pPoolstatus();
    pClientStatus();
    pMemStatus();
 //   pFDStatus();
 //   pComeEvent();

}
void coreGui::wComeEvent(int n)
{
    if(coreGui::core==NULL)
            return ;
    coreGui::core->nfds_event=n;

}
void coreGui::wListenFd(int fd)
{
    if(coreGui::core==NULL)
            return ;
    coreGui::core->fds[fd]++;
}
void coreGui::wEpollstatus(int maxE,int curE,int countW)
{
    if(coreGui::core==NULL)
        return ;
    coreGui::core->maxEvent=maxE;
    coreGui::core->curEvent=curE;
    coreGui::core->countWake=countW;

}
void coreGui::wPoolstatus(int maxTh,int workTh,int curTh,int waitTa)
{
    if(coreGui::core==NULL)
        return ;
    coreGui::core->maxThreads=maxTh;
    coreGui::core->curThreads=curTh;
    coreGui::core->workThreads=workTh;
    coreGui::core->waitTask=waitTa;

}
void coreGui::wClientStatus(int count)
{
    if(coreGui::core==NULL)
        return ;
    coreGui::core->packetCount=count;

}
void coreGui::wMemStatus(int count,int err)
{
    if(coreGui::core==NULL)
        return ;
    coreGui::core->memCount=count;

    coreGui::core->memErrCount=err;


}



 void coreGui::pEpollstatus()
 {
     printf("\033[?25l\033[5;4H  ------当前EPOLL 状态------ \033[0m");
     printf("\033[?25l\033[6;4H  最大监听事件数:%d    当前监听事件数: %d  当前唤醒次数: %d\033[0m",maxEvent,curEvent,countWake);



 }
 void coreGui::pPoolstatus()
 {

     printf("\033[?25l\033[7;4H  ------当前线程池 状态------ \033[0m");
     printf("\033[?25l\033[8;4H  最大线程数:%d    当前线程数: %2d  工作线程: %2d  当前等待队列: %10d\033[0m",maxThreads,curThreads,workThreads,waitTask);


 }
 void coreGui::pClientStatus()
 {

     printf("\033[?25l\033[9;4H  ------当前客户端任务 前置 状态------ \033[0m");
     printf("\033[?25l\033[10;4H  总接收的数据包： %d \033[0m",packetCount);

 }
 void coreGui::pMemStatus()
 {
     printf("\033[?25l\033[11;4H  ------当前客户端任务 后置 状态------ \033[0m");
     printf("\033[?25l\033[12;4H  成功发送的数据包： %d   发送失败： %d\033[0m",memCount,memErrCount);



 }


void coreGui::clrScreen()
{

    printf("\033[2J");
}

 void coreGui::pComeEvent()
 {
     printf("\033[?25l\033[13;4H nfds= %d \033[0m",nfds_event);


 }


 void coreGui::pFDStatus()
 {
     printf("\033[?25l\033[15;4H  ------当前响应的客户端 状态------ \033[0m");
     int n=16;
     for(auto it:fds)
     {
         printf("\033[?25l\033[%d;4H  fd ： %d  响应： %d 次  \033[0m",n++,it.first,it.second);
     }



 }

