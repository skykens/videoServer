#ifndef CPTHREADMUTEX_H
#define CPTHREADMUTEX_H

#include <stdio.h>
#include <pthread.h>

class CPThreadMutex
{
public:
    CPThreadMutex();
    ~CPThreadMutex();
    bool lock();
    bool unlock();
    bool trylock();//非阻塞上锁
protected:
    pthread_mutex_t m_mutex;
};

#endif // CPTHREADMUTEX_H
