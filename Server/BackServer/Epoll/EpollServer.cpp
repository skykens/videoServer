#include "EpollServer.h"


EpollServer::EpollServer(int maxThread,int set_event,int port,unsigned int maxEvent,const char * ip, int timeout)
    :EpollBase(maxEvent,timeout)
{
     log=EpollLog::getInstance();
    threadPool=new ThreadPool(maxThread,20);
    defevent=set_event;
    server=new TCPServer(100,port,ip);  //自动绑定并监听
    if(!AddEvent(server->getfd(),EPOLLIN)) //添加监听事件
    {
        log->writeError("前置服务器初始化失败");
        exit(EXIT_FAILURE);
    }
    printf("EpollServer init .....\n");
    threadPool->addTask((TaskBase *)new ListenClientTask(&clients,&signal));
    sleep(1);
    threadPool->addTask((TaskBase *)new ListenMemTask());
    sleep(1);
    printf("EpollServer init  successful!!!\n");

}
void EpollServer::run()
{
    int nfds,client_fd;
    TCPClient *client,*target;
    log->writeInfo("前置服务器初始化成功");
    while(1)
    {

        if(m_bStop)
            continue;
        nfds=Wait();  //等待连接
        signal.Lock();
        switch(nfds)
        {
        case -1:
            if(errno!=EINTR)
            {
                log->writeError("errno!=EINTR");
                exit(EXIT_FAILURE);
            }
            break;
        case -2:
            log->writeError("epoll stop");
            break;
        default:
            for(int n=0;n<nfds;n++)
            {
                if(m_retEvent[n].data.fd==server->getfd())
                {  //有新客户端进来
                    client_fd=server->m_accept();
                    if (client_fd == -1)
                    {
                        log->writeError("accept error");
                        exit(EXIT_FAILURE);
                    }
                    client=new TCPClient(client_fd,server->GetSockaddr());
                    if(!client->setNonBlocking())
                        log->writeError("set nun blocking false");
                    log->writeInfo("new client host:"+ string(client->GetHostIP())
                                   +" connected.");
                    if(AddEvent(client->getfd(),Getdefevent()))
                    {
                        clients.push_back(client);
                       log->writeInfo("总客户端数 ："+to_string(clients.size()));
                    }
                    else
                    {
                        delete client;
                    }

                }else if((target=findClientFd(m_retEvent[n].data.fd))!=NULL&&(m_retEvent[n].events==EPOLLIN))
                {  //客户端事件响应  从线程池取出一个线程处理事件
                    //   client_fd=Epoll->m_retEvent[n].data.fd;//客户端
                    TCPPacket *handlePack=new TCPPacket(target);
                    //  Epoll->DelEvent(target->getfd(),EPOLLIN);
                    //note1:需要把客户端的请求处理完，否则会持续保存在Epoll事件组中
                    log->writeInfo("fd:"+to_string(target->getfd())
                                   +"收到数据包");

                    threadPool->addTask((TaskBase *)new ClientTask(handlePack));
                }

                break;

            }




        }

        signal.unLock();
    }
    signal.unLock();
    log->writeError("error!!!");


}


TCPClient* EpollServer::findClientFd(int fd)
{
    int begin,end,count;
    count=clients.size();
    if(count<4)
    {
        for(int i=0;i<count;i++)
        {
            if(clients[i]->getfd()==fd)
                return clients[i];
        }
    }else
    {
        //使用二分查询
        int low = 0 ,high = count , middle;
        while(low < high)
        {
            middle = (low + high)/2;
            if(fd == clients[middle]->getfd())
                return clients[middle];
            else if(fd > clients[middle]->getfd())
                low = middle +1;
            else if(fd < clients[middle]->getfd())
                high = middle;
        }

    }
    return NULL;


    
}
