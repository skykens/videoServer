/*************************************************************************
    > File Name: BackServer.cpp
    > Author:
    > Mail:
    > Created Time: 2019年10月27日 星期日 10时57分13秒
 ************************************************************************/

#include "BackServer.h"


BackServer::BackServer(int maxThread,safeQueue<char *> & que):buf_que(que),Pardata(que)
{
    Pardata.start();

}
void BackServer::run()
{
    CShmFIFO *m_recvFIFO=CShmFIFO::GetinterfaceRecv(KEY_FIFO_RECV,MAX_PACKET,1000);
    while(1)
    {
        char *buf=(char *)malloc(MAX_PACKET);
        m_recvFIFO->read(buf);
        buf_que.push(buf);
        Pardata.wakeUp();
    }
}



