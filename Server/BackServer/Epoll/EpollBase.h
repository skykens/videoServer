#ifndef EPOLLBASE_H
#define EPOLLBASE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
/*************************************************************************
    > File Name: EpollBase.h
    > Author:
    > Mail:
    > Created Time: 2019年09月27日 星期五 12时52分02秒
    >需要在 子类里 定义  接口run()，用于epoll_wait()函数的运行
 ************************************************************************/
#define KEY_FIFO_SEND   ftok("/", 1)
#define KEY_FIFO_RECV   ftok("/", 2)
class EpollBase
{
public:
    EpollBase(unsigned int maxEvent = 200, int timeout = -1);
    ~EpollBase();
    bool AddEvent(int fd, unsigned int events);  //添加事件
    bool ModEvent(int fd, unsigned int events);
    bool DelEvent(int fd, unsigned int events);
    inline void SetTimeout(const int timeout){m_timeout=timeout;}
    inline int GetTimeout()const{return m_timeout;}
    inline virtual void Stop(){m_bStop=true;}
    inline virtual void Start(){m_bStop=false;}
    inline int Wait()
    {
        if(!m_bStop)
           return epoll_wait(m_epfd,m_retEvent,m_maxEvent,m_timeout);
        else
            return -2;

    }
    inline int GetMaxevent(){return m_maxEvent;}


protected:    //目的是让子类能调用
    int m_maxEvent;  //并发的最大事件
    int m_nowEvent;  //现在所监听的事件数
    struct epoll_event *m_retEvent;  //保存描述符事件的数组
    int m_epfd;       //epoll监视描述符
    int m_timeout;    //超时时间
    bool m_bStop;     //结束标记
    struct epoll_event m_event;  //用于增加删除等操作

};

#endif //_EPOLLBASE_H_
