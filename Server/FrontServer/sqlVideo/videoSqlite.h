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
#include <string.h>
#include "../Thread/M_Condition.h"
#include "../../common/NetPacket/public.h"
class videoSqlite :public SqliteBase
{
    public:
       static videoSqlite *GetInterface();
       virtual char ** m_exec(const char *sql,char **errmsg=NULL);
       int Login( login_t *,char **);
       int Register(myregister_t  *,char **);
       int SendRequestList(sqlite3_callback fun ,void *data,char **errmsg);

//        int insertUser(char *userName,char *password);
//        int searchUser(char *userName,char *password==NULL);
//        int isOnline(char *userName);
//        int insertVideo(char *)
//        int insertVideo(int videoID,char *videoName,int chanlID,int areaID,int startNUM,char *photoURL,char *netURL)
//        int getAllVideo();
//        int insertHistory(int userID,int videoID,struct tm time,int len);
//        int searchHistory(int userID);
    private:
        videoSqlite(const char *filename);
        virtual void createTable();

        static int callback(void *NotUsed, int argc, char **argv, char **azColName);
        char **Getval();
    private:
        M_Condition* mutex;

        static videoSqlite *sqiteVideo;
        char **argv;//获得回调函数的参数
        int argc; //获得回调函数的个数

};
#endif
