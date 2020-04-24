/**
 * Project Untitled
 */


#include "ThreadPoolTask.h"

/**
 * ThreadPoolTask implementation
 */
ThreadPoolTask::ThreadPoolTask(ThreadPool* ow) :owner(ow)
{
    m_task=NULL;
    task_is_running=false;
    freeFlag=false;   //刚创建出来60s内不会变成空闲线程
    setDetach();

}

bool ThreadPoolTask::wakeUp()
{
    return !cond.Signal();

}
ThreadPoolTask::~ThreadPoolTask()
{
    if(m_task)
    {
        for(int i=0;task_is_running;i++)
        {
          //等待任务结束
          if(i==INT_MAX)
          {
                //time out 日志
              std::cout<<"delete ThreadPool Task timeout\n"<<endl;
              break;
          }

        }
        delete m_task;
    }
}
/**
 * @return void
 */
bool ThreadPoolTask::setTask(TaskBase *task) {
    m_task=task;
    return wakeUp();
}

/**
 * @return bool
 */
bool ThreadPoolTask::isFree()
{
    return freeFlag;
}
bool ThreadPoolTask::isRunning()
{
    return task_is_running;
}

/**
 * @return void
 */
void ThreadPoolTask::run() {

    cond.timeWait(60);  //阻塞等待60s  超时了自己再检查以下 同时将线程置为空闲
    if(m_task!=NULL)
    {
        task_is_running=true;
        freeFlag=false; //清0 重新开始
        m_task->run();

        try{
           delete m_task;   //删除对象
        }catch(exception e)
        {
            cout<<"delete m_task error"<<endl;
            //日志系统

        }
        m_task=NULL;
        task_is_running=false;
        owner->free_deq.push(this);

    }else
        freeFlag=true;  //60s到的时候还是没有任务;

}
