/**
 * Project Untitled
 */


#ifndef _THREADPOOLTASK_H
#define _THREADPOOLTASK_H
#include <climits>
#include <iostream>
#include "ThreadBase.h"
#include "./Task/TaskBase.h"
#include "ThreadPool.h"
#include "M_Condition.h"
using namespace std;
class ThreadPool;
class ThreadPoolTask: public ThreadBase {
public:
    ThreadPoolTask(ThreadPool* ow);
    ~ThreadPoolTask();
    bool setTask(TaskBase*task);
    void setRunning(){task_is_running=true;}
    bool wakeUp();
    bool isRunning();
    bool isFree();
private:
    void run();
private: 
    M_Condition  cond;  //统一 唤醒 等待
    TaskBase * m_task;
    ThreadPool* owner;
    bool task_is_running;
    bool freeFlag; //空闲时间 空闲时间超过1min就可以删除了

};

#endif //_THREADPOOLTASK_H
