/**
 * Project Untitled
 */
#include "TaskLog.h"
TaskLog *  TaskLog::m_taskLog=NULL;
TaskLog::TaskLog():LogBase("Task_Log")
{
    filename="./Frontlog/Task_Log";
    init();
}


TaskLog * TaskLog::getInstance()
{
    if(!m_taskLog)
        m_taskLog=new TaskLog();
    return m_taskLog;

}

void TaskLog::init() {
    addFileAppender(filename);
    return;
}
