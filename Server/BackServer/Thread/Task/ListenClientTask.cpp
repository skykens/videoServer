#include "ListenClientTask.h"

ListenClientTask::ListenClientTask(unordered_map<int,TCPClient*> &source,M_Condition *clientMutex,EpollBase *server)
    :clients(source),signal(clientMutex)
{
    log=TaskLog::getInstance();
    Epoll=server;
}

void ListenClientTask::run()
{
    log->writeInfo("客户端心跳监听线程启动");
    //遍历查看客户端是否有超时的   有就删除  释放所有资源
    while(1)
    {
        if(clients.empty())
            continue;  //为空的时候重新循环
        sleep(1);
        for (auto it = clients.begin(); it!=clients.end();)
        {
            TCPClient* tmp = it->second;
            tmp->Timesub();   //心跳自减
            if(tmp->isTimeout()||tmp->isDie())
            {
                tmp->lock();  //先加锁
                //error 错误 删除 还没有改 在Epoll模型里面需要删除事件
                Epoll->DelEvent(tmp->getfd(),EPOLLIN);  //删除对应的事件
                TCPClient *del=it->second;
                log->writeInfo("hots:"+string(del->GetHostIP())
                               +"已经断开连接");
                clients.erase(it);
                delete del;
                signal->unLock();
            }else
                it++;

        }

    }
}
