#include "EpollBase.h"


EpollBase::EpollBase(unsigned int maxEvent , int timeout )
{
    m_nowEvent=0;
    m_bStop=false;
    m_maxEvent=maxEvent;
    m_timeout=timeout;
    m_epfd=epoll_create(maxEvent);
    if(!(m_retEvent=(struct epoll_event* )malloc(sizeof(struct epoll_event)*m_maxEvent)))
    {
        perror("malloc error !");
        exit(EXIT_FAILURE);
    }

    if(m_epfd==-1)
    {
        perror("epoll_create error");
    }



}

EpollBase::~EpollBase()
{

}

bool EpollBase::AddEvent(int fd, unsigned int events)
{
    if(fd<0)
        return false;
    struct epoll_event m_event;
    m_event.events=events;
    m_event.data.fd=fd;
    if((m_nowEvent+1)>m_maxEvent)
    {
       printf("too many fd");
        return false;
    }

    if(epoll_ctl(m_epfd,EPOLL_CTL_ADD,fd,&m_event)<0)
    {
        perror("AddEvent error");
        return false;
    }else
        {
        m_nowEvent++;
        return true;
    }
}

bool EpollBase::ModEvent(int fd, unsigned int events)
{
    if(fd<0)
        return false;
    struct epoll_event m_event;
    m_event.events=events;
    m_event.data.fd=fd;
    if(epoll_ctl(m_epfd,EPOLL_CTL_MOD,fd,&m_event)<0)
    {
        perror("ModEvent error");
        return false;
    }else
        {
        return true;
    }

}

bool EpollBase::DelEvent(int fd, unsigned int events)
{
    if(fd<0)
        return false;
    struct epoll_event m_event;
    m_event.events=events;
    m_event.data.fd=fd;
    if(epoll_ctl(m_epfd,EPOLL_CTL_DEL,fd,&m_event)<0)
    {
        perror("DelEvent error");
        return false;
    }else
    {
        m_nowEvent--;
        return true;
    }

}


