#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include "ThreadBase.h"
#include "ThreadPoolTask.h"
#include "M_Condition.h"
#include "Lock.h"
#include <iostream>
#include "safeQueue.hpp"
#include <unordered_set>
using namespace std;
class ThreadPoolTask;
class ThreadPool:  protected ThreadBase
{
public: 
    ThreadPool(int,int);
    ~ThreadPool();
    void start();
    void stop();
    bool addTask(TaskBase *);
private:
    void init();
    void run();
    void auto_reduce();  //缩容策略
    void auto_expand();  //扩容策略
private: 
    M_Condition mute;
    safeQueue<ThreadPoolTask *> free_deq;  //等待任务

    safeQueue<TaskBase *> wait_deq;  //等待队列
    const int max_threads;   //最大线程数
    const int core_threads; //核心线程数
    int count_threads; //总线程数
 friend class ThreadPoolTask;

};

#endif //_THREADPOOL_H
