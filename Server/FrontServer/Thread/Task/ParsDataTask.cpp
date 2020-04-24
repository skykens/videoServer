#include "ParsDataTask.h"

ParsDataTask::ParsDataTask(RequestPacket *m_packet)
    :packet(m_packet)
{

}
void ParsDataTask::run()
{
    CShmFIFO *m_sendFIFO=CShmFIFO::GetinterfaceSend(KEY_FIFO_SEND,MAXPACKET,100);
    videoSqlite *sql=videoSqlite::GetInterface();
    int user_id=0,val=0;
    RelayPacket *relay=new RelayPacket(packet->GetFd());
    char *errmsg;
    if(!packet->isRight())
    {
        packet->writeError("packet error!\n");
        m_sendFIFO->write(packet->Tochar());
        return ;
        //写出错包回共享内存
    }
    char *data=packet->Getwork()->body;
    //写日志信息
    switch(packet->getfuncid())   //这里可用多态进行改进
    {
    case T_login:

        printf("T_login\n");
        user_id=sql->Login((struct request_login*)data,&errmsg);
        if(user_id>0)
        {
            relay->Login(user_id,true);

        }else
        {
            relay->Login(user_id,false);
        }

        break;
    case T_register:
        printf("T_register\n");

        if((user_id=sql->Register((struct request_register*)data,&errmsg))>0)
        {
            relay->Regist(user_id, true);

        }else
        {
            relay->Regist(user_id, false);
        }
        break;
    case T_requestList:
        printf("T_requestList\n");
        val=sql->SendRequestList(SendList,(void *)relay,&errmsg);
        if(val<0)
        {
            packet->writeError("packet error!\n");
            m_sendFIFO->write(packet->Tochar());
            return ;
            //写出错包回共享内存
        }else
        {
            return ;  //写包已经在回调函数中做完了
        }

        break;
    case T_uploadHistory:
        printf("T_uploadHistory\n");
        if(sql->UploadHistory((struct request_uploadHistory*)data,&errmsg)>0)
        {
            relay->UploadHistory(true);

        }else
        {
            relay->UploadHistory(false);
        }
        break;

    }
    sqlite3_free(errmsg);
    m_sendFIFO->write(relay->Tochar());
}


int ParsDataTask::SendList(void *data, int argc, char **argv, char **azColName)
{
    CShmFIFO *m_sendFIFO=CShmFIFO::GetinterfaceSend(KEY_FIFO_SEND,MAXPACKET,100);
    RelayPacket *relay=(RelayPacket *)data;
    struct relay_videList videoList;
    int i;
    printf("start sendlist\n");
    videoList.video_count=argc;
    strcpy(videoList.video_name,argv[1]);
    videoList.class_id=atoi(argv[2]);
    videoList.type_id=atoi(argv[3]);
    videoList.area_id=atoi(argv[4]);
    videoList.play_times=atoi(argv[5]);
    videoList.is_new=0;
    strcpy(videoList.video_imageURL,argv[6]);
    strcpy(videoList.video_address,argv[7]);
    relay->Videolist(&videoList,i,argc);
    m_sendFIFO->write(relay->Tochar());
    return 0;
}

