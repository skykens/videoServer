#ifndef PACKETBASE_H
#define PACKETBASE_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PACKET_HEAD 0x0505
#define PACKET_END 0x5050
#define MAXPACKET (sizeof(videoPacket)+sizeof(struct relay_videList)+sizeof(videoPacketEnd))
enum funType{
    T_keepActive=0,
    T_login,
    T_register,
    T_requestList,
    T_uploadHistory
};

struct packet_access{  //用于存储包信息
     short body_size;  //work中body的大小
     char seq;  //序号
     char sum; //总数
     int client_fd; //服务端用，包对应客户端的文件套接字
     short trans_id; //包流水 ，待定
     char error_msg[30] ;//出错信息
     bool is_error;  //出错标志位
     char check_crc[4] ;//crc校验码 保留 待定
     char funcid;//功能号
 };

typedef struct videoPacket_t
{
    short head;
    struct packet_access info;
}videoPacket;
struct packet_work
{
    char *body; //可变数组
};
typedef short  videoPacketEnd;
//不同类型的数据包
struct request_login{
    char soft_ver[6];//版本号
    char username[20];
    char pwd[6];
};
struct relay_login{
    int user_id;//用户id号
    bool login_ret;//结果
};
struct request_register
{
    char soft_ver[6];//版本号
    char username[20];
    char pwd[6];
    char email[20];

};
struct relay_register
{
    int user_id;
    bool register_ret;
};
struct requeset_fun
{
    char non;  //空字符
};
struct relay_videList
{
    int video_count;  //应答的视频总数
    char class_id;   //频道id
    char type_id;  //类型id
    char area_id;  //地区id
    char video_name[64];  //视频名称
    int play_times;   //播放次数
    bool is_new; //是否是新上传的 （待定）
    char video_imageURL[256];  //视频图片地址
    char video_address[256];  //视屏地址
};
struct request_uploadHistory
{
    int user_id;
    int video_id;  //视屏id
    int vide_seek;  //播放位置
    char update_flowid[23];
    //上传数据流水；平台生成；格式：YYYYMMDDHHMISS+func_id+5位随机数

};
struct relay_uploadHistory
{
    bool result; //1:成功   0：失败
    char update_flowid[23];
//上传数据流水；平台生成；格式：YYYYMMDDHHMISS+func_id+5位随机数
};
////
class PacketBase
{
public:
    PacketBase();
     int setBody(int size);
     virtual int writeError(const char *errmsg);
    virtual inline  int getSize(){return sizeof(videoPacket);}
     struct packet_work *Getwork(){return &body;}

    ~PacketBase();
protected:
    virtual char* Tochar()=0; //获得char[]
    virtual videoPacket* Getpacket()=0;  //获得packet指针
protected:
    int count;
    int Maxsize;
    videoPacket *m_packet;
   struct packet_work body;
    char *src;
   // struct packet_work *m_body;  //数据内容核心
  //  char *m_data;
};

#endif // TEXTPACK_H
