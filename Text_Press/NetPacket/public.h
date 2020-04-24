#ifndef PUBLIC_H
#define PUBLIC_H
/*****************
功能号funcId:
0 代表心跳包
0001 代表登录
0002 代表注册包
1001 代表频道包
1002 代表类型包
1003 代表地区包
1004 代表视频详细信息包
**********************/

#define PACKET_HEAD 0x0404
#define PACKET_END 0x0505
enum funType{
    T_keepActive=0,
    T_login=1,
    T_register=2,
    T_class=1001,
    T_videotype,
    T_area,
    T_vidolist

};

/*总的包*/
typedef struct config_data_t
{
    int min_config;
    bool switch_answer;
    int sec_config;
    int clint_num;
    bool switch_Login;//是否登录成功
    bool switch_register;// 是否注册成功
    bool switch_channel;
    bool switch_type;//类型
    bool switch_area;//地区
    bool switch_video_list;
    bool switch_play_flowid;//播放流动
    bool switch_video_play;//视频播放
    bool switch_time_flowid;
    bool switch_video_time;//时间流动
}config_data;

/*******************接入层数据包头***************************/
typedef struct Packet_Head_T //总包包头、包括各业务的
{
    int  fd;  //对应客户端的套接字
    int  func_id; //功能码
    int  optid;  //可选项
    int  packet_size;  //包的大小
    int  packet_seq;  //包序号
    int  packet_sum;  //包总数
    int  trans_id;  //流水号
    int  crc;//数据包的校验码
    int  error_code;//错误代码：0-代表正确;
    char error_msg[30]; //错误信息
   // char srcAddr[6]; //预留  //源地址
   // char dstAddr[6]; //预留  目的地址

    int  packet_head;  // 标志头

}packet_head_t;

/*******************数据总包-包尾***************************/
typedef struct Packet_Tail_T //用来判断接收的数据是否是完整的
{
    int packet_tail;//包尾0x0505
}packet_tail_t;

/*******************数据总包***************************/
typedef struct Packet_All_T          /*需要改*/                    //用来判断接收的数据是否是完整的
{
    packet_head_t  head;                             //总包包头，包括业务功能号
    char* data;           //业务数据包
    packet_tail_t  tail;                             //总包包尾
}packet_all_t;

/*******************业务-心跳包***************************/
//func_id=0000
typedef struct Heart_Beat_T
{
    int fd; //客户端fd
    bool flag;//心跳状态，true-在线，flase-离线
}heart_beat_t;

/*******************业务-客户端登录***************************/
//func_id=0001;
typedef struct Login_T
{
        char  username[20];  //用户名-限定最大11位
        char  psw[10];	//用户密码-限定6位
}login_t;

/*******************业务-服务器应答登录***********************/
//func_id=0001;
typedef struct Res_Login_T
{
        int user_id;  //用户ID号
        int  login_ret;	//登入应答结果0-登录成功；1-账号错误；2-密码错误；
}res_login_t;


/*******************业务-客户端注册***************************/
//func_id=0002;
typedef struct myRegister_T
{
        char  username[20];  //用户名-限定最大11位
        char  psw[10];	//用户密码-限定6位
        char  psw_question[20];	//密保问题
        char  psw_answer[20];	//密保答案
}myregister_t;

/*******************业务-服务器应答注册***************************/
//func_id=0002;
typedef struct Res_Register_T
{
        int  user_id;  //产生用户ID号
        int  register_ret;//注册应答结果0-登录成功；1-账号错误；2-密码错误；
}res_register_t;

/****************业务-客户端请求视频的频道分类**********************/
//func_id=1001;
typedef struct Class_T
{

}class_t;
/****************业务-服务器应答请求频道分类**********************/
//func_id=1001;
typedef struct Res_Class_T
{
        int  classes_count;//频道分类数量
        int  classes_id;//频道分类id
        char classes_name[20];//频道分类名称
}res_class_t;

/****************业务-客户端请求视频类型分类**********************/
//func_id=1002;
typedef struct Type_T
{

}type_t;
/****************业务-服务器应答请求类型分类**********************/
//func_id=1002;
typedef struct Res_Type_T
{
        int  type_count;//类型分类数量
        int  classes_id;//依据上面频道分类id
        int  type_id;//视频类型分类id
        char type_name[20];//视频类型分类名称
}res_type_t;

/****************业务-客户端请求视频类型分类**********************/
//func_id=1003;
typedef struct Area_T
{

}area_t;
/****************业务-服务器应答请求地区分类**********************/
//func_id=1003;
typedef struct Res_Area_T
{
        int  area_count;//地区分类数量
        int  classes_id;//依据上面频道分类id
        int  area_id;//视频地区分类id
        char area_name[20]; //视频地区分类名称
}res_area_t;

/****************业务-客户端请求视频列表**********************/
//func_id=1004;
typedef struct Video_List_T
{
    int  page; //当前页 从1开始
    int  vidoe_num; //视频请求数量
    int  classes_id;//频道id
    int  type_id; //类型id
    int  area_id;//地区id
}video_list_t;
/****************业务-服务器应答请求视频列表*******************/
//func_id=1004;
typedef struct Res_Video_List_T
{
        int  video_count;//视频数量
        int  video_id;//视频id
        int  classes_id;//频道id
        int  type_ids[10]; //类型id、最多10个分类
        int  area_id;//地区id
        char video_name[64];//视频名称
        int  play_times;//播放次数
        char is_new;//0-旧视频，1-新视频
        char video_image[256];//视频封面图片链接地址
        char video_address;//视频网络链接地址
}res_video_list_t;

/****************业务-客户端视频点播-请求流水号**********************/
//func_id=2001;
typedef struct Play_Flowid_T
{

}play_flowid_t;
/****************业务-服务器应答视频点播-流水号*******************/
//func_id=2001;
typedef struct Res_Play_Flowid_T
{
        char update_flowid[24];//流水号格式：YYYYMMDDHHMMSS+func_id+5位随机数
}res_play_flowid_t;
/****************业务-客户端视频点播**********************/
//func_id=2001;
typedef struct Video_Play_T
{
        int  user_id;//用户id
        int  video_id;//视频id
        char update_flowid[24];//流水号格式：YYYYMMDDHHMMSS+func_id+5位随机数
}video_play_t;
/****************业务-服务器应答视频点播*******************/
//func_id=2001;
typedef struct Res_Video_Play_T
{
        int  resulte;//上传结果。0--成功、1--失败
        char update_flowid[24];//流水号格式：YYYYMMDDHHMMSS+func_id+5位随机数
}res_video_play_t;


/****************业务-客户端上传时长-请求流水号**********************/
//func_id=2002;
typedef struct Time_Flowid_T
{

}time_flowid_t;
/****************业务-服务器应答上传时长-流水号*******************/
//func_id=2002;
typedef struct Res_Time_Flowid_T
{
    char xstop_time[20];//格式：YYYYMMDDHHMMSS
    unsigned int  random; //随机数 0~65536
}res_time_flowid_t;
/****************业务-客户端视频上传点播时长**********************/
//func_id=2002;
typedef struct Video_Time_T
{
        int  user_id;//用户id
        int  video_id;//视频id
        int  video_seek;//点播时长
        char update_flowid[24];//流水号格式：YYYYMMDDHHMMSS+func_id+5位随机数
        unsigned int  random; //随机数 0~65536
}video_time_t;
/****************业务-服务器应答上传时长*******************/
//func_id=2002;
typedef struct Res_Video_Time_T
{
        int  resulte;//上传结果。0--成功、1--失败
        char update_flowid[24];//流水号格式：YYYYMMDDHHMMSS+func_id+5位随机数
}res_video_time_t;

#define MAX_PACKET (sizeof(packet_head_t)+sizeof(res_video_list_t)+sizeof(packet_tail_t))
#endif // PUBLIC_H
