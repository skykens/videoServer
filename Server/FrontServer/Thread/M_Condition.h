#ifndef M_CONDITION_H
#define M_CONDITION_H
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
class M_Condition
{
public:
    M_Condition();
    ~M_Condition()
    {
         Destroy();
    }
    int Lock()  ;
    int unLock() ;
    int Wait() ;
    int timeWait(int sec_times) ;
    int Signal() ;
    int Broadcast() ;
private:
    int Destroy();

private:
    pthread_mutex_t pmutex;
    pthread_cond_t pcond;
};

#endif // M_CONDITION_H
