#ifndef CBASETHREAD_H
#define CBASETHREAD_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

class CBaseThread
{
public:
    CBaseThread();  //此时还没有创建线程，只有类对象
    ~CBaseThread();
    void start(); //创建线程并启动线程
    virtual int run() = 0;  //用户自定义处理函数，在派生类中必须实现

protected:
    pthread_t m_tid;  //线程ID
    bool m_bRun;      // 运行标记
private:
    static void * rountine(void *arg);   //线程类处理函数框架
};

#endif // CBASETHREAD_H
