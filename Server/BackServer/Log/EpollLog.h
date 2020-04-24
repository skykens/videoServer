#ifndef EPOLLLOG_H
#define EPOLLLOG_H

#include <iostream>
#include "LogBase.h"
using namespace std;
class EpollLog :protected LogBase
{
public:
    static EpollLog *getInstance();
    inline void writeError( string error){ErrorLog_out(error);}
    inline void writeInfo(string info){InfoLog_out(info);}
    void init();
private:
    EpollLog();
private:
    static EpollLog* m_EpollLog;
    string filename;
};


#endif // EPOLLLOG_H
