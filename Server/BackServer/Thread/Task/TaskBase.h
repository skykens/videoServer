/**
 * Project Untitled
 */


#ifndef _TASKBASE_H
#define _TASKBASE_H
#include <iostream>
class TaskBase {

public :
    TaskBase();
    virtual  ~TaskBase(){}
    virtual void run() = 0;

protected: 
    int type;
    void * retval;
    void * error;

};

#endif //
