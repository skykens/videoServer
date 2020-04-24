#include "CEpollBase.h"

CEpollBase::CEpollBase(unsigned int maxEvent, int timeout)
{
    m_timeout = timeout;
    m_maxEvent = maxEvent;
    m_bStop = false;

    m_retEvent = new epoll_event[m_maxEvent];
    if (m_retEvent == NULL)
    {
        perror("Event error\n");
    }
    memset(m_retEvent,0,m_maxEvent);
    memset(&m_event,0,sizeof(struct epoll_event));
    //创建epoll
    m_epfd = epoll_create(m_maxEvent);
    if (m_epfd == -1)
    {
        perror("epoll error\n");
    }
}

CEpollBase::~CEpollBase()
{
    if (m_epfd)
    {
        close(m_epfd);
    }
    if (m_retEvent!=NULL)
    {
        delete[]m_retEvent;
    }
}

bool CEpollBase::AddEvent(int fd, unsigned int events)
{
    int res;
    memset(&m_event, 0, sizeof(struct epoll_event));
    m_event.events = events;
    m_event.data.fd = fd;
    res = epoll_ctl(m_epfd, EPOLL_CTL_ADD, fd, &m_event);
    if (res != 0)
    {
        perror("epoll_ctl error \n");
        return false;
    }
    return true;
}

bool CEpollBase::ModEvent(int fd, unsigned int events)
{
    int res;
    memset(&m_event, 0, sizeof(struct epoll_event));
    m_event.events = events;
    m_event.data.fd = fd;
    res = epoll_ctl(m_epfd, EPOLL_CTL_MOD, fd, &m_event);
    if (res != 0)
    {
        perror("epoll_ctl error \n");
        return false;
    }
    else
    {
        return true;
    }
}

bool CEpollBase::DelEvent(int fd, unsigned int events)
{
    int res;
    memset(&m_event, 0, sizeof(struct epoll_event));
    m_event.events = events;
    m_event.data.fd = fd;
    res = epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd, &m_event);
    if (res != 0)
    {
        perror("epoll_ctl error \n");
        return false;
    }
    else
    {
        return true;
    }
}

void CEpollBase::SetTimeout(const int timeout)
{
    m_timeout = timeout;
}

int CEpollBase::GetTimeout()const
{
    return m_timeout;
}

int CEpollBase::Wait()
{
    int res;
    res = epoll_wait(m_epfd, m_retEvent, m_maxEvent, m_timeout);
    if (res < 0)
    {
        perror("epoll_wait error\n");
    }
    else if (res == 0)
    {
        printf("timeout\n");
    }
    return res;
}

void CEpollBase::Start()
{
    while (!m_bStop)
    {
        int nevent = Wait();
        if (nevent)
        {
            Run(nevent);
        }
    }
}

void CEpollBase::Stop()
{
    m_bStop = true;
}
