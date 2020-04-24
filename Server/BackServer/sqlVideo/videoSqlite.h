/*************************************************************************
	> File Name: videoSqlite.h
	> Author: 
	> Mail: 
	> Created Time: 2019年10月26日 星期六 16时35分10秒
 ************************************************************************/

#ifndef _VIDEOSQLITE_H
#define _VIDEOSQLITE_H
#include "SqliteBase.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include "../../common/NetPacket/NetPacket.h"
using namespace clientPacket;
class videoSqlite :public SqliteBase
{
    public:
       static videoSqlite *GetInterface();
       virtual char ** m_exec(const char *sql);
       const char * Errormsg();
       int Login(login &src);
       int Register(regist &src);
        char **videoList();

    private:
        videoSqlite(const char *filename);
        virtual void createTable();

        static int callback(void *NotUsed, int argc, char **argv, char **azColName);
        char **Getval();
    private:
        char errmsg[30]={0};
        static videoSqlite *sqiteVideo;
        char **argv;//获得回调函数的参数
        int argc; //获得回调函数的个数

};
#endif
