#ifndef THREADLOG_H
#define THREADLOG_H

#include "LogBase.h"
#include <iostream>
#include <string>
using namespace std;
class ThreadLog: protected LogBase {
public:
    ~ThreadLog(){}
    static ThreadLog *getInstance();
    inline void writeError( string error){ErrorLog_out(error);}
    inline void writeInfo(string info){InfoLog_out(info);}
private:
    ThreadLog();
    void init();
private:
    static ThreadLog* m_ThreadLog;
    string filename;

};

#endif // THREADLOG_H
