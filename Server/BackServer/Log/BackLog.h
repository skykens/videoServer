#ifndef BACKLOG_H
#define BACKLOG_H
#include "LogBase.h"
#include <string>
#include <iostream>
using namespace std;
class BackLog :protected LogBase
{
public:
    static BackLog *getInstance();
    inline void writeError( string error){ErrorLog_out(error);}
    inline void writeInfo(string info){InfoLog_out(info);}


private:
    void init();
    BackLog();
private:
    static BackLog* m_BackLog;
    string filename;


};
#endif // BACKLOG_H
