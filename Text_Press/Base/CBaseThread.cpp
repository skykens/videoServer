#include "CBaseThread.h"

CBaseThread::CBaseThread()
    :m_bRun(false)
{

}

CBaseThread::~CBaseThread()
{

}

void CBaseThread::start()
{
    if(m_bRun == false)
    {
        if(pthread_create(&m_tid,NULL,rountine,(void *)this) != 0)
        {
            perror("create thread error:\n");
        }
    }
}

void * CBaseThread::rountine(void *arg)
{
    pthread_detach(pthread_self());
    CBaseThread *thr = (CBaseThread *)arg;

    thr->m_bRun = true;
    thr->run();
    thr->m_bRun = false;

    pthread_exit(NULL);
}
