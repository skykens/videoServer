/**
 * Project Untitled
 */


#include "ThreadPool.h"

/**
 * ThreadPool implementation
 */


ThreadPool::ThreadPool(int maxThreads,int defaultThread)
     :max_threads(maxThreads),count_threads(defaultThread),
     core_threads(defaultThread)
{
    setDetach();
    init();
}
void ThreadPool::init() {
    for(int i=0;i<count_threads;i++)
    {
        ThreadPoolTask *temp=new ThreadPoolTask(this);
        temp->Thread_start(true);
        free_deq.push(temp);
    }

}



void ThreadPool::start() {
    Thread_start(true);
    return;
}


void ThreadPool::stop() {
    Thread_stop();
    return;
}


bool ThreadPool::addTask(TaskBase *target) {

    wait_deq.push(target);
//       mute.Lock();
//       if(free_deq.empty())
//       {
//           wait_deq.push(target);
//       }
//       else
//       {
//           ThreadPoolTask * tmp=free_deq.front();
//           free_deq.pop();
//           mute.unLock();
//           return tmp->setTask(target);
//       }
//       mute.unLock();
       return true;

}



void ThreadPool::run() {

    while(1)
    {
    //用于处理 任务等待队列的任务

    while(wait_deq.size())
    {
        if(free_deq.size())
        {
            TaskBase *tmp=wait_deq.front();
            wait_deq.pop();
            ThreadPoolTask *Threadtmp=free_deq.front();
            free_deq.pop();
            Threadtmp->setTask(tmp);
        }else
            break;

    }
    if(free_deq.empty())
        auto_expand();
    }
    if(wait_deq.empty()&&free_deq.size()>core_threads)
        auto_reduce();
    //缩容策略
    return;
}
void ThreadPool::auto_reduce()
{

    Lock lock(mute);
    while(free_deq.size()&&count_threads>core_threads)
    {
        ThreadPoolTask * tmp=free_deq.front();
        if(!tmp->isFree())
            break;
        free_deq.pop();
        delete tmp;
        count_threads--;

    }



}
void ThreadPool::auto_expand() {


    int n=count_threads;
    if(max_threads-n>5)
        n=5;
   else
        n=max_threads-n;
    while(n--)
    {
        ThreadPoolTask *temp=new ThreadPoolTask(this);
        temp->Thread_start(true);
        free_deq.push(temp);
        count_threads++;
    }


}


ThreadPool::~ThreadPool(){
    stop();
    while(free_deq.size())
    {
        ThreadPoolTask *tmp= free_deq.front();
        delete tmp;
        //日志   删除线程池
    }

}
