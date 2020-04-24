#ifndef TASKEPOLL_H
#define TASKEPOLL_H

#include <QRunnable>
#include "CEpollClient.h"
#include <QDebug>
class TaskEpoll : public QRunnable
{
public:
    TaskEpoll(int ClientSum,CHostAddress myaddr);
    CEpollClient *myEpollClient;
    void run();
};

#endif // TASKEPOLL_H
