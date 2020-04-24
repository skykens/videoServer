#ifndef MALLOCLOG_H
#define MALLOCLOG_H

#include <iostream>
#include "LogBase.h"

using namespace std;
class MallocLog:protected LogBase
{
public:
    static MallocLog *getInstance();
    inline void writeError( string error){ErrorLog_out(error);}
    inline void writeInfo(string info){InfoLog_out(info);}
    void init();
    ~MallocLog(){}
protected:
    MallocLog();
private:
    static MallocLog* m_MallocLog;
    string filename;
};






#endif // MALLOCLOG_H
