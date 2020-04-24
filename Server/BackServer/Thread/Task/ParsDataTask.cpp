#include "ParsDataTask.h"

ParsDataTask::ParsDataTask(void *m_packet)
{
    buf=malloc(MAX_PACKET);
    memcpy(buf,m_packet,MAX_PACKET);
}
void ParsDataTask::run()
{
    CShmFIFO *m_sendFIFO=CShmFIFO::GetinterfaceSend(KEY_FIFO_SEND,MAX_PACKET,1000);
    videoSqlite *sql=videoSqlite::GetInterface();
    int user_id=0,val=0;
    char *errmsg;
    //可以增加一个CRC校验;
    //写日志信息
    packet_head_t* head=(packet_head_t*)buf;

    switch(head->func_id)   //这里可用多态进行改进
    {

    case T_login:
       { clientPacket::login login;
       // printf("T_login\n");
        if(!login.data.ParseFromArray(buf+sizeof(packet_head_t),head->packet_size))
        {
            printf("error   \n");
            //出错 发送错误包
        }

        user_id=sql->Login(login,&errmsg);
        if(user_id>0)
        {
            serverPacket::login login(head->fd);
            login.data.set_userid(user_id);
            login.data.set_ret(true);
            login.SerializeToArray(buf,MAX_PACKET);


        }else
        {
            //设置错误信息
        }

        break;
        }
    case T_register:
    {
        printf("T_register\n");

        break;
    }

    case T_vidolist:
     {
        printf("T_requestList\n");
//        val=sql->SendRequestList(SendList,(void *)relay,&errmsg);
//        if(val<0)
//        {
//            packet->writeError("packet error!\n");
//            m_sendFIFO->write(packet->Tochar());
//            return ;
//            //写出错包回共享内存
//        }else
//        {
//            return ;  //写包已经在回调函数中做完了
//        }

        break;
        }
//    case T_uploadHistory:
//        printf("T_uploadHistory\n");
//        if(sql->UploadHistory((struct request_uploadHistory*)data,&errmsg)>0)
//        {
//            relay->UploadHistory(true);

//        }else
//        {
//            relay->UploadHistory(false);
//        }
//        break;

    }
//    sqlite3_free(errmsg);
    m_sendFIFO->write(buf);
}


int ParsDataTask::SendList(void *data, int argc, char **argv, char **azColName)
{
//    CShmFIFO *m_sendFIFO=CShmFIFO::GetinterfaceSend(KEY_FIFO_SEND,MAXPACKET,1000);
//    RelayPacket *relay=(RelayPacket *)data;
//    struct relay_videList videoList;
//    int i;
//    printf("start sendlist\n");
//    videoList.video_count=argc;
//    strcpy(videoList.video_name,argv[1]);
//    videoList.class_id=atoi(argv[2]);
//    videoList.type_id=atoi(argv[3]);
//    videoList.area_id=atoi(argv[4]);
//    videoList.play_times=atoi(argv[5]);
//    videoList.is_new=0;
//    strcpy(videoList.video_imageURL,argv[6]);
//    strcpy(videoList.video_address,argv[7]);
//    relay->Videolist(&videoList,i,argc);
//    m_sendFIFO->write(relay->Tochar());
    return 0;
}

ParsDataTask::~ParsDataTask()
{
    if(buf)
        free(buf);
}
