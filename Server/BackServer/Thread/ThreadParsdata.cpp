#include "ThreadParsdata.h"

ThreadParsdata::ThreadParsdata(safeQueue<char *> & safe):buf_que(safe),buf_tmp(NULL)
{
    sql=videoSqlite::GetInterface();


}

void ThreadParsdata::wakeUp()
{
    cond.Signal();
}

void ThreadParsdata::run()
{
    while(buf_que.empty())
        cond.Wait(); //避免虚假唤醒
    buf_tmp=buf_que.front();
    buf_que.pop();
    static CShmFIFO *m_sendFIFO=CShmFIFO::GetinterfaceSend(KEY_FIFO_SEND,MAX_PACKET,1000);
    //可以增加一个CRC校验;
    //写日志信息
    packet_head_t* head=(packet_head_t*)buf_tmp;
    switch(head->func_id)   //这里可用多态进行改进
    {

    case T_login:
    {
        login();
        break;
    }
    case T_register:
    {
        break;
    }
    case T_vidolist:
    {

        break;
    }
    }
    m_sendFIFO->write(buf_tmp);
    free(buf_tmp);
}
void ThreadParsdata::login()
{
    packet_head_t* head=(packet_head_t*)buf_tmp;
    clientPacket::login client_login;
    serverPacket::login server_login(head->fd);
    if(!client_login.data.ParseFromArray(buf_tmp+sizeof(packet_head_t),head->packet_size))
    {
        server_login.setErrmsg("data error ! Please check agagin .");
        server_login.SerializeToArray(buf_tmp,MAX_PACKET);
        return;
        //出错 发送错误包
    }
    int user_id=sql->Login(client_login);
    if(user_id>0)
    {

       server_login.data.set_userid(user_id);
    }else
    {
        server_login.data.set_userid(0);
        server_login.data.set_ret(false);

        server_login.setErrmsg(sql->Errormsg());
        //设置错误信息

    }
    server_login.SerializeToArray(buf_tmp,MAX_PACKET);




}
void ThreadParsdata::registe()
{
    packet_head_t* head=(packet_head_t*)buf_tmp;
    clientPacket::regist client_regist;
    serverPacket::regist server_regist(head->fd);
    if(!client_regist.data.ParseFromArray(buf_tmp+sizeof(packet_head_t),head->packet_size))
    {
        server_regist.setErrmsg("data error ! Please check agagin .");
        server_regist.SerializeToArray(buf_tmp,MAX_PACKET);
        return;
        //出错 发送错误包
    }
    int user_id=sql->Register(client_regist);
    if(user_id>0)
    {
        server_regist.data.set_userid(user_id);
        server_regist.data.set_ret(true);
    }else
    {
        server_regist.setErrmsg(sql->Errormsg());
        //设置错误信息

    }
    server_regist.SerializeToArray(buf_tmp,MAX_PACKET);








}


