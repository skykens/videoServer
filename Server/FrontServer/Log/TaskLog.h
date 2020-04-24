/**
 * Project Untitled
 */


#ifndef _TASKLOG_H
#define _TASKLOG_H

#include "LogBase.h"
#include <iostream>
#include <string>
using namespace std;
class TaskLog: protected LogBase {
public: 
    ~TaskLog(){}
    static TaskLog *getInstance();
    inline void writeError( string error){ErrorLog_out(error);}
    inline void writeInfo(string info){InfoLog_out(info);}
private:
    TaskLog();
    void init();
private: 
    static TaskLog* m_taskLog;
    string filename;

};

#endif //_TASKLOG_H
