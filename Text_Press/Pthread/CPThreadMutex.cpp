#include "CPThreadMutex.h"
#include <iostream>
using namespace std;

CPThreadMutex::CPThreadMutex()
{
    if(pthread_mutex_init(&m_mutex,NULL)!=0)
    {
        perror("pthread mutex init error\n");
    }
}

CPThreadMutex::~CPThreadMutex()
{
    if(pthread_mutex_destroy(&m_mutex)!=0)
    {
        perror("pthread mutex destroy error\n");
    }
}

bool CPThreadMutex::lock()
{
    int ret=pthread_mutex_lock(&m_mutex);
    if (ret !=0)
    {
        perror("pthread mutex lock error\n");
    }
    if(ret ==0)
    {
        return true;
    }
    else
    {
        return false;
    }
    return ret==0 ? true: false;
}

bool CPThreadMutex::unlock()
{
    int ret=pthread_mutex_unlock(&m_mutex);
    if (ret !=0)
    {
        perror("pthread mutex unlock error\n");
    }
    return ret==0 ? true: false;
}

bool CPThreadMutex::trylock()
{
    int ret=pthread_mutex_trylock(&m_mutex);
    if (ret !=0)
    {
        perror("pthread mutex trylock error\n");
    }
    return ret==0 ? true: false;
}
