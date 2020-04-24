/**
 * Project Untitled
 */


#ifndef _LOGSYSTEM_H
#define _LOGSYSTEM_H
#include "LogBase.h"
#include <vector>
using namespace std;
class LogSystem {
public: 
    LogSystem();
   ~ LogSystem();
    void addLogger(LogBase *);
private: 
    vector <LogBase *> log_vect;
};

#endif //_LOGSYSTEM_H
