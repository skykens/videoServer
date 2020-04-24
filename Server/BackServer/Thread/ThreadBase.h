#ifndef THREADBASE_H
#define THREADBASE_H
#include <pthread.h>
#include <errno.h>

class ThreadBase
{
public:
    ThreadBase();
    virtual  ~ThreadBase();
    int initBase();  //线程初始化
    virtual void run()=0;   //运行的内容
    int Thread_start(bool isLoop);   //是否循环的开始
    inline int join(void **retval) {return pthread_join(pid,retval);}
    const pthread_t getpid(){return pid;}
    int setDetach();
    void Thread_stop();
protected:
    static void* function(void *);
    pthread_t pid;
    pthread_attr_t *attr;  //线程属性
    bool Loop;  //循环与否
    bool isStart;   //线程是否开始




};

#endif // THREADBASE_H
