#include "ListenMemTask.h"

ListenMemTask::ListenMemTask(unordered_map<int,TCPClient*>  &cli):clients(cli)
{


}

void ListenMemTask::run()
{
    char  *buf=(char *)malloc(MAX_PACKET);
    static int count=0,errcount=0;
    CShmFIFO *m_sendFIFO=CShmFIFO::GetinterfaceSend(KEY_FIFO_SEND,MAX_PACKET,1000);
    //log->writeInfo("共享内存监听线程已经启动");
    while(1)
    {

        m_sendFIFO->read((void *)buf);


        packet_head_t * head=(packet_head_t *)buf;
        int size=head->packet_size+sizeof(packet_head_t)+sizeof(packet_tail_t);
        if(write(head->fd,buf,size)<0)
        {
            ++errcount;
        //    writeError("发送应答包出错");

        }
        else
        {

            coreGui::wMemStatus(++count,errcount);
        }

    }

}
