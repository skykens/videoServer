#include "ListenMemTask.h"

ListenMemTask::ListenMemTask()
{

    log=TaskLog::getInstance();

}

void ListenMemTask::run()
{
    char  *buf=(char *)malloc(MAX_PACKET);

    CShmFIFO *m_sendFIFO=CShmFIFO::GetinterfaceSend(KEY_FIFO_SEND,MAX_PACKET,100);
    log->writeInfo("共享内存监听线程已经启动");
    while(1)
    {

        m_sendFIFO->read((void *)buf);


        log->writeInfo("从MemFIFO读到数据");
        packet_head_t * head=(packet_head_t *)buf;
        int size=head->packet_size+sizeof(packet_head_t)+sizeof(packet_tail_t);
        TCPClient client(head->fd);
        if(client.sendPacket(buf,size)<0)
            log->writeError("发送应答包出错");
        else
            log->writeInfo("To "+string(to_string(client.getfd()))
                           +"发送应答包成功");
    }

}
