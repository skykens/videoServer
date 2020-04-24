#ifndef CTHREADPOOL_H
#define CTHREADPOOL_H

#include <list>
#include "CPThreadCond.h" //条件变量
#include <unistd.h>
#include "Task.h"
using namespace std;

class CThreadPool
{
public:
    CThreadPool(unsigned int max=77,unsigned int min=77,unsigned int wait=60);
    ~CThreadPool();
    void addTask(Task *task);
    void createThread();
    void createThread(int NumCreate);
    void destroy();

    static void *handler(void *arg);  //非静态，create报错？
    unsigned int m_maxcount;
    unsigned int m_mincount;
    unsigned int m_count; //当前线程数
    unsigned int m_waitcount;  //空闲线程数
    unsigned int m_waitsec;
    list<Task *> m_taskList;
    CPThreadCond m_cond;
    bool m_bStop;  //启动线程销毁？  启动 == true 不销毁 == false
};

#endif // CTHREADPOOL_H
