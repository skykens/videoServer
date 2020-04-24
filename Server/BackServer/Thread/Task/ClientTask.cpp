#include "ClientTask.h"

ClientTask::ClientTask(TCPClient &m_client)
    :client(m_client),log(TaskLog::getInstance())
{

}
void ClientTask::run()
{

    CShmFIFO *m_recvFIFO=CShmFIFO::GetinterfaceRecv(KEY_FIFO_RECV,MAX_PACKET,100);
    if(client.isDie())
    {
        log->writeError(string(client.GetHostIP())
                        +"断开连接");
        return ;
    }
    if(client.recvPacket()<0)
        log->writeError("ClientTask: recvPacket error");
    else{
        log->writeInfo("fd: "+to_string(client.getfd())+
                    "host:"+string(client.GetHostIP())
                       +"获得正确数据包");
        m_recvFIFO->write(client.readBuf());    //放到共享内存里
    }



}
