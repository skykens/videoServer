#include "EpollServer.h"


EpollServer::EpollServer(int maxThread,int defThread,int set_event,int port,unsigned int maxEvent,const char * ip, int timeout)
    :EpollBase(maxEvent,timeout)
{
    event_count=0;
     log=EpollLog::getInstance();
    threadPool=new ThreadPool(maxThread,defThread);
    threadPool->start();
    defevent=set_event;
    server=new TCPServer(1024,port,ip);  //自动绑定并监听
    if(!AddEvent(server->getfd(),EPOLLIN)) //添加监听事件
    {
        log->writeError("前置服务器初始化失败");
        exit(EXIT_FAILURE);
    }
 //   threadPool->addTask((TaskBase *)new ListenClientTask(clients,&signal,this));
    sleep(1);
    threadPool->addTask((TaskBase *)new ListenMemTask(clients));
    sleep(1);


}
void EpollServer::run()
{
    int nfds,client_fd;

    ////log->writeInfo("Front Server初始化成功");
//    cout<<"当前m_recvFIFO共享内存KEY:"<<to_string(KEY_FIFO_RECV)<<endl;
//    cout<<"当前m_sendFIFO共享内存KEY:"<<to_string(KEY_FIFO_SEND)<<endl;
    while(1)
    {

        coreGui::wEpollstatus(m_maxEvent,m_nowEvent,event_count);
        if(m_bStop)
            continue;
        nfds=Wait();  //等待连接
        //signal.Lock();
        switch(nfds)
        {
        case -1:
            if(errno!=EINTR)
            {
                log->writeError("errno!=EINTR");
                exit(EXIT_FAILURE);
            }  //处理中断恢复
            break;
        case -2:
            log->writeError("epoll stop");
            break;
        default:
          //  coreGui::wComeEvent(nfds);
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
                    TCPClient *client;
                    client=new TCPClient(client_fd,server->GetSockaddr());
                    if(!client->setNonBlocking())
                        log->writeError("set nun blocking false");
                    if(AddEvent(client->getfd(),Getdefevent()))
                    {
                     //   coreGui::wListenFd(client->getfd());
                        clients.insert(make_pair(client->getfd(),client));
                    }
                    else
                    {
                        delete client;
                    }

                }else if(clients.count(m_retEvent[n].data.fd)
                         &&(m_retEvent[n].events==EPOLLIN))
                {
                    event_count++;
                 //  coreGui::wListenFd(m_retEvent[n].data.fd);  //测试用
                   threadPool->addTask((TaskBase *)new ClientTask(*clients[m_retEvent[n].data.fd],this));



                }

            }




        }




    }






    log->writeError("error!!!");


}

void EpollServer::removeClient(int fd)
{
    if(clients.count(fd))
    {
        TCPClient *tmp = clients[fd];
        clients.erase(fd);
        delete tmp;
    }

}
