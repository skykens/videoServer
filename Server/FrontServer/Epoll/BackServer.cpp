/*************************************************************************
    > File Name: BackServer.cpp
    > Author:
    > Mail:
    > Created Time: 2019年10月27日 星期日 10时57分13秒
 ************************************************************************/

#include "BackServer.h"


BackServer::BackServer(int maxThread)
{
    m_bStop=true;
    threadPool=new ThreadPool(maxThread,20);
}
void BackServer::run()
{

    char *buf=(char *)malloc(MAXPACKET);
    CShmFIFO *m_recvFIFO=CShmFIFO::GetinterfaceRecv(KEY_FIFO_RECV,MAXPACKET,100);
    while(!m_bStop)
    {
        m_recvFIFO->read(buf);
        printf("start pardata in backserver!\n");
        threadPool->addTask(new ParsDataTask(new RequestPacket(buf)));
    }

}



