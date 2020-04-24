#ifndef CPTHREADCOND_H
#define CPTHREADCOND_H

#include "CPThreadMutex.h"
#include <sys/time.h>
#include <errno.h>

class CPThreadCond : public CPThreadMutex
{
public:
    CPThreadCond();
    ~CPThreadCond();
    bool wait();
    bool timewait(unsigned int sec); //被唤醒 == true  超时或出错 == false
    bool signal();
    bool broadcast();
    bool isTimeout();
private:
    pthread_cond_t m_cond;
    bool m_btimeout;
};

#endif // CPTHREADCOND_H
