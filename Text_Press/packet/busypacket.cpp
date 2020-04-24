#include "busypacket.h"

BusyPacket::BusyPacket(int no)
    : CBasePacket(sizeof(Packet_All_T))
{
    memset(&head, 0, sizeof(Packet_Head_T));
//    memset(&nature, 0, sizeof(Packet_Nature_T));
    memset(&tail, 0, sizeof(Packet_Tail_T));

    head.packet_head=0x0404;//包头
    head.packet_size=sizeof(body);//包的大小
    head.optid=0x01;
    head.packet_seq=0;
    head.packet_sum=1;
    head.trans_id=0;
    head.fd=0;

    printf("head1 : %x\n",head.packet_head);

    tail.packet_tail=0x0505;//包尾
    printf("tail 1 : %x\n",tail.packet_tail);
    switch(no)
    {

        case 1:login_Packet();
        break;
        case 2:register_Packet();
        break;
        case 3:class_Packet();
        break;
        case 4:type_Packet();
        break;
        case 5:area_Packet();
        break;
        case 6:video_list_Packet();
        break;
        case 7:play_flowid_Packet();
        break;
        case 8:video_play_Packet();
        break;
        case 9:time_flowid_Packet();
        break;
        case 10:video_time_Packet();
        break;
        case 11:hreat_Packet();
        break;
        default:break;
    }
}

BusyPacket::~BusyPacket()
{

}

int BusyPacket::pack()
{
    memcpy(m_data, &this->head, sizeof(packet_head_t));
    memcpy(m_data+sizeof(packet_head_t),this->body, sizeof(body));
//    memcpy(m_data+sizeof(packet_head_t)+sizeof(body),&this->nature, sizeof(packet_nature_t) );
    memcpy(m_data+sizeof(packet_head_t)+sizeof(body), &this->tail, sizeof(packet_tail_t) );
    return 0;
}

int BusyPacket::unpack()
{
    return 0;
}

void BusyPacket::hreat_Packet()
{
//    head.func_id = 0000;
//    this->pack();
}

void BusyPacket::login_Packet()
{
    printf("head2 : %x\n",head.packet_head);
    head.func_id = 0x01;//****///
    /// \brief Body
    body=(char *)malloc(sizeof(login_t));
    login_t *Body=(login_t*)body;
    strcpy(Body->username,"admin");
    strcpy(Body->psw,"123456");

    this->pack();
}

void BusyPacket::register_Packet()//注册包定义
{
    head.func_id = 0002;
    myregister_t *Body=(myregister_t*)body;
    strcpy(Body->username,"wang");
    strcpy(Body->psw,"123456");
    strcpy(Body->psw_question,"my name is");
    strcpy(Body->psw_answer,"wangzixin");
    this->pack();
}

void BusyPacket::class_Packet()
{
    head.func_id = 1001;
    this->pack();
}

void BusyPacket::type_Packet()
{
    head.func_id = 1002;
    this->pack();
}

void BusyPacket::area_Packet()
{
    head.func_id = 1003;
    this->pack();
}

void BusyPacket::video_list_Packet()
{
    head.func_id = 1004;
    video_list_t *Body=(video_list_t*)body;
    Body->page=1;
    Body->vidoe_num=3;
    Body->classes_id=101;
    Body->type_id=200;
    Body->area_id=300;
    this->pack();
}

void BusyPacket::play_flowid_Packet()//业务交易流水
{
    head.func_id = 2001;
    head.packet_seq = 1;
    this->pack();
}

void BusyPacket::video_play_Packet()//请求应答包
{
    head.func_id = 2001;
    head.packet_seq = 2;
    video_play_t *Body = (video_play_t *)body;
    Body->user_id = 1;
    Body->video_id = 1;
    QString str = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    this->pack();
}

void BusyPacket::time_flowid_Packet()
{
    head.func_id = 2002;
    head.packet_seq = 1;
    this->pack();
}

void BusyPacket::video_time_Packet()
{
    head.func_id = 2002;
    head.packet_seq = 2;
    video_time_t *Body = (video_time_t*)body;
    Body->user_id = 10001;
    Body->video_id = 8001;
    Body->video_seek = 99;
    Body->random = 123456;
    strcpy(Body->update_flowid,"20191030155631");
    this->pack();
}

char *BusyPacket::getBody()
{
    return this->body;
}
