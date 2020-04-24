#include "BackLog.h"
BackLog* BackLog::m_BackLog=NULL;
BackLog::BackLog():LogBase("Back_Log")
{
    filename="./Backlog/Back_Log";
    init();


}


void BackLog::init()
{
    addFileAppender(filename);
    return;
}
BackLog* BackLog::getInstance()
{
    if(!m_BackLog)
        m_BackLog=new BackLog();
    return m_BackLog;
}

