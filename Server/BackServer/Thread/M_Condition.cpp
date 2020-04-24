#include "M_Condition.h"
M_Condition::M_Condition()
{
    int val;
    if((val=pthread_mutex_init(&pmutex,NULL)))
            perror("mutex error.");
    if((val=pthread_cond_init(&pcond,NULL)))
            perror("cond error.");
}

int M_Condition::Lock()
{
    return pthread_mutex_lock(&pmutex);
}

int M_Condition::unLock()
{
    return pthread_mutex_unlock(&pmutex);

}

int M_Condition::Wait()
{
    return pthread_cond_wait(&pcond,&pmutex);
}

int M_Condition::timeWait(int sec_times)
{
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME,&abstime);
    abstime.tv_sec+=sec_times;
    return pthread_cond_timedwait(&pcond,&pmutex,&abstime);

}

int M_Condition::Signal()
{
    return pthread_cond_signal(&pcond);

}

int M_Condition::Broadcast()
{
    return pthread_cond_broadcast(&pcond);
}

int M_Condition::Destroy()
{
    int val;
    if((val=pthread_mutex_destroy(&pmutex))<0)
    {
        perror("mutex destroy error");
        return val;
    }
    if((val=pthread_cond_destroy(&pcond))<0)
    {
        perror("cond destroy error");
        return val;
    }
    return 0;

}
