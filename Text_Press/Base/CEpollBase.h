#ifndef CEPOLLBASE_H
#define CEPOLLBASE_H

#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

class CEpollBase
{
public:
    CEpollBase(unsigned int maxEvent = 1000000, int timeout =10);
    ~CEpollBase();
    bool AddEvent(int fd, unsigned int events);
    bool ModEvent(int fd, unsigned int events);
    bool DelEvent(int fd, unsigned int events);
    void SetTimeout(const int timeout);
    int GetTimeout()const;
    int Wait();
    void Start();
    void Stop();
protected:
    struct epoll_event *m_retEvent;  //接收返回事件
    //struct epoll_event m_retEvent[maxEvent];
    int m_maxEvent;
private:
    virtual void Run(int nevent) = 0;
    int m_epfd;
    struct epoll_event m_event;  //用于epoll增、删、改
    int m_timeout;
    bool m_bStop; //配合Stop关闭Epoll监听和事件处理
};

#endif // CEPOLLBASE_H
