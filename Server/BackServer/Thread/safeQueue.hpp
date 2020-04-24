#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <queue>
#include "M_Condition.h"
#include "Lock.h"
template <class T>
class safeQueue
{
public:
    safeQueue(){}
    void pop(){
        Lock lock(mutex);
        que.pop();
    }
    void push(T elem)
    {
        Lock lock(mutex);
        que.push(elem);

    }
    T front()
    {
        Lock lock(mutex);
        return que.front();
    }
    T back()
    {
        Lock lock(mutex);
        return que.back();
    }
    int size()
    {
        Lock lock(mutex);
        return que.size();
    }
    bool empty()
    {
        Lock lock(mutex);
        return que.empty();
    }
private:
    M_Condition mutex;
    std::queue<T> que;
};

#endif // SAFEQUEUE_H
