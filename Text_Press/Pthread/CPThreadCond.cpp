#include "CPThreadCond.h"
#include<iostream>
using namespace std;
CPThreadCond::CPThreadCond()
{
    this->m_btimeout = false;
    if(pthread_cond_init(&m_cond,NULL) == -1)
    {
        perror("pthread_cond error\n");
    }
}

CPThreadCond::~CPThreadCond()
{
    if(pthread_cond_destroy(&m_cond) == -1)
    {
        perror("pthread_cond_destroy error\n");
    }
}

bool CPThreadCond::wait()
{
    if(pthread_cond_wait(&m_cond,&m_mutex) == -1)
    {
        return false;
    }
    return true;
}

bool CPThreadCond::timewait(unsigned int sec)
{
    struct timeval nowtime;
    struct timespec settime;
    gettimeofday(&nowtime,NULL);
    settime.tv_sec = nowtime.tv_sec + sec;
    settime.tv_nsec = nowtime.tv_usec * 1000;
    int ret=pthread_cond_timedwait(&m_cond,&m_mutex,&settime);
    if(ret==ETIMEDOUT)
    {
        m_btimeout = true;
        return false;
    }
    else if(ret!=0)
    {
        perror("pthread_cond_timewait");
    }
    return ret==0 ? true:false;
}

bool CPThreadCond::signal()
{
    int ret = pthread_cond_signal(&m_cond);
    if(ret == -1)
    {
        return false;
    }
    return true;
}

bool CPThreadCond::broadcast()
{
    int ret = pthread_cond_broadcast(&m_cond);
    if(ret == -1)
    {
        perror("pthread_cond_broadcast error\n");
        return false;
    }
    return true;
}

bool CPThreadCond::isTimeout()
{
    return m_btimeout;
}
