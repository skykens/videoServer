#include "MallocLog.h"

MallocLog *  MallocLog::m_MallocLog=NULL;
MallocLog::MallocLog():LogBase("MallocLog")
{
    filename="./Frontlog/MallocLog";
    init();

}


MallocLog * MallocLog::getInstance()
{
    if(!m_MallocLog)
        m_MallocLog=new MallocLog();
    return m_MallocLog;

}

void MallocLog::init() {
    addFileAppender(filename);
    return;
}
