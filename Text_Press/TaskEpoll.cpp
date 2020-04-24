#include "TaskEpoll.h"

TaskEpoll::TaskEpoll(int ClientSum,CHostAddress myaddr)
{
    myEpollClient=new CEpollClient(ClientSum,myaddr);
}
void TaskEpoll::run()
{
    myEpollClient->Start();
}
