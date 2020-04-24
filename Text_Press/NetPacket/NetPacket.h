#ifndef NETPACKET_H
#define NETPACKET_H
#include "PacketBase.h"

class LoginPacket :public PacketBase
{
public:
    LoginPacket(char *src,int size):PacketBase(src,size){}
    LoginPacket(){}
    inline const login_t * getBody(){return (login_t *)body;}
    virtual bool isError();
    ~LoginPacket();
private:
};

class RegisPacket :public PacketBase
{
public:
    RegisPacket(char *src,int size):PacketBase(src,size){}
    RegisPacket(){}
    inline const  myregister_t* getBody(){return (myregister_t *)body;}
    virtual bool isError();
    ~RegisPacket();
private:



};

class KeepActivePacket :public PacketBase
{
public:
    KeepActivePacket(char *src,int size):PacketBase(src,size){}
    KeepActivePacket(){}
    inline const  heart_beat_t* getBody(){return (heart_beat_t *)body;}
    virtual bool isError();
    ~KeepActivePacket();
private:


};


class ClassPacket :public PacketBase
{
public:
    ClassPacket(char *src,int size):PacketBase(src,size){}
    ClassPacket(){}
    inline const  class_t* getBody(){return (class_t *)body;}
    virtual bool isError();
    ~ClassPacket();
private:

};


class VideoTypePacket :public PacketBase
{
public:
    VideoTypePacket(char *src,int size):PacketBase(src,size){}
    VideoTypePacket(){}
    inline const  type_t* getBody(){return (type_t *)body;}
    virtual bool isError();
    ~VideoTypePacket();
private:


};

class AreaPacket :public PacketBase
{
public:
    AreaPacket(char *src,int size):PacketBase(src,size){}
    AreaPacket(){}
    inline const  area_t* getBody(){return (area_t *)body;}

    virtual bool isError();
    ~AreaPacket();
private:


};


class VideoListPacket :public PacketBase
{
public:
    VideoListPacket(char *src,int size):PacketBase(src,size){}
    VideoListPacket(){}
    inline const  video_list_t* getBody(){return (video_list_t *)body;}
    virtual bool isError();
    ~VideoListPacket();
private:


};










#endif // NETPACKET_H
