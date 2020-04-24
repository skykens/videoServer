#include "ClientTask.h"

ClientTask::ClientTask(TCPClient &m_client,EpollServer *ba)
    :client(m_client),base(*ba)
{

}
void ClientTask::run()
{

    static int count=0;
    CShmFIFO *m_recvFIFO=CShmFIFO::GetinterfaceRecv(KEY_FIFO_RECV,MAX_PACKET,1000);
    if(client.isDie())
    {
       // writeError(string(client.GetHostIP())
        //                +"断开连接");
        return ;
    }

    try
    {
    while(client.recvPacket()>0)
    {



        m_recvFIFO->write(client.readBuf());    //放到共享内存里
        static M_Condition mut;
        mut.Lock();
        count++;
        mut.unLock();
    }
    }catch(const char *err)
    {

        base.DelEvent(client.getfd(),EPOLLIN|EPOLLONESHOT);
       // writeError("fd="+to_string(client.getfd())+" close");
        base.removeClient(client.getfd());
        return ;

    }
    if(!base.ModEvent(client.getfd(),EPOLLIN|EPOLLONESHOT))
    {
        string err(const_cast<char *>(strerror(errno)));
       // writeError("fd="+to_string(client.getfd())+"  err:"+err);

    }
    coreGui::wClientStatus(count);


}
