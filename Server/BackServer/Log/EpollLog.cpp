#include "EpollLog.h"

EpollLog *  EpollLog::m_EpollLog=NULL;
EpollLog::EpollLog():LogBase("Epoll_Log")
{
    filename="./Frontlog/Epoll_Log";
    init();

}


EpollLog * EpollLog::getInstance()
{
    if(!m_EpollLog)
        m_EpollLog=new EpollLog();
    return m_EpollLog;

}

void EpollLog::init() {
    addFileAppender(filename);
    return;
}
