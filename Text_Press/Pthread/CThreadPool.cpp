#include "CThreadPool.h"

CThreadPool::CThreadPool(unsigned int max,unsigned int min,unsigned int wait)
{
    this->m_maxcount = max;
    this->m_mincount = min;
    this->m_count = 0;
    this->m_waitcount = 0;
    this->m_waitsec = wait;
    this->m_bStop = false;

    m_cond.lock();
    createThread(min);
    m_cond.unlock();
}

CThreadPool::~CThreadPool()
{
    destroy();
}

void CThreadPool::addTask(Task *task)
{
    m_cond.lock();
    m_taskList.push_back(task);
    m_cond.unlock();
}

void CThreadPool::createThread()
{
    pthread_t tid;
    if(pthread_create(&tid, NULL, handler,(void *)this ) != 0)
    {
        perror("pthread_create");
    }
    else
        m_count++;
}

void CThreadPool::createThread(int NumCreate)
{
    for(int i=0;i<NumCreate&&m_count<m_maxcount-2;i++)
    {
        createThread();
    }
}

void CThreadPool::destroy()
{
    m_bStop = true;
    while(m_count)
    {
        m_cond.lock();
        m_cond.broadcast();
        m_cond.unlock();
        sleep(1);
    }
}

void *CThreadPool::handler(void *arg)
{
    pthread_detach(pthread_self());
    CThreadPool *pool = (CThreadPool *)arg;
    while (1)
    {
        pool->m_cond.lock();
        while ( !pool->m_taskList.empty())
        {
            Task *task = pool->m_taskList.front();
            pool->m_taskList.pop_front();
            pool->m_cond.unlock();
            task->run();
            delete task;
            pool->m_cond.lock();
        }
        if (pool->m_taskList.empty())
        {
            pool->m_waitcount++;
            bool bSignal = pool->m_cond.timewait(2); //超时false
            pool->m_waitcount--;

            if(((!bSignal && pool->m_count > pool->m_mincount) || pool->m_bStop) && pool->m_taskList.empty())  //保留min线程数
            {
                pool->m_count--;
                pool->m_cond.unlock();

                if(!bSignal)
                {
                    printf("pthread[0x%x] timeout exit\n", (int)pthread_self());
                }
                else
                {
                    printf("pthread[0x%x] exit\n", (int)pthread_self());
                }
                pthread_exit(NULL);
            }
        }
        pool->m_cond.unlock();
    }
    return NULL;
}
