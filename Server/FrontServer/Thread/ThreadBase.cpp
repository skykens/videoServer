#include "ThreadBase.h"

ThreadBase::ThreadBase():attr(NULL),Loop(false),isStart(false)
{
    if(initBase()<0)
    {
        throw ("create Thread error:"+errno);
    }

}
ThreadBase::~ThreadBase()
{
    Thread_stop();
    pthread_cancel(pid);
    join(NULL);

}
int ThreadBase::initBase()
{
    return pthread_create(&pid,attr,function,this);

}

int ThreadBase:: Thread_start(bool isLoop)   //是否循环的开始
{

    isStart=true;
    Loop=isLoop;
}
int ThreadBase:: setDetach()
{
    return  pthread_detach(pid);
}

void ThreadBase:: Thread_stop()
{
    isStart=false;
}

void* ThreadBase:: function(void *arg)
{
    ThreadBase *base=(ThreadBase *)arg;
    do
    {
        if(base->isStart)
         {
            base->run();
            if(!base->Loop)
             {
                pthread_exit(NULL);
            }
        }
    }while(1);


}

