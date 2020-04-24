#ifndef LOCK_H
#define LOCK_H
#include "M_Condition.h"
class Lock
{
public:
    Lock(M_Condition & );
    ~Lock();
private:
    void *operator new(size_t);
    Lock* operator=(Lock&);
private:
    M_Condition & mutex;
};

#endif // LOCK_H
