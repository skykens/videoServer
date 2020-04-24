#include "Lock.h"


Lock::Lock(M_Condition &mute) :mutex(mute)
{
    mutex.Lock();

}
Lock::~Lock()
{
    mutex.unLock();

}
