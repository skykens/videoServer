#include "ThreadLog.h"
ThreadLog *  ThreadLog::m_ThreadLog=NULL;
ThreadLog::ThreadLog():LogBase("Thread_Log")
{
    filename="./Frontlog/Thread_Log";
    init();
}


ThreadLog * ThreadLog::getInstance()
{
    if(!m_ThreadLog)
        m_ThreadLog=new ThreadLog();
    return m_ThreadLog;

}

void ThreadLog::init() {
    addFileAppender(filename);
    return;
}
