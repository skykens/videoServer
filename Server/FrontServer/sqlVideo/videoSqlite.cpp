/*************************************************************************
    > File Name: videoSqlite.cpp
    > Author:
    > Mail:
    > Created Time: 2019年10月26日 星期六 16时35分09秒
 ************************************************************************/
#include "videoSqlite.h"
videoSqlite* videoSqlite::sqiteVideo=NULL;
videoSqlite *videoSqlite::GetInterface()
{
    if(sqiteVideo==NULL)
        sqiteVideo=new videoSqlite("videoSql.db");
    return sqiteVideo;




}

videoSqlite::videoSqlite(const char *filename)
    :SqliteBase(filename)
{
    argv=NULL;
    argc=0;
    mutex=new M_Condition();
    createTable();

}
void videoSqlite::createTable()
{
    char *Errmsg=0;
    const char *sql1="CREATE TABLE USER ("  \
                     "ID INTEGER PRIMARY KEY   AUTOINCREMENT  ," \
                     "NAME           TEXT    NOT NULL," \
                     "PASSWORD           TEXT     NOT NULL," \
                     "ONLINEFLAG        CHAR(1)  );";
    const char *sql2="CREATE TABLE HISTORY ("  \
                     "USER_ID INTEGER PRIMARY KEY     NOT NULL," \
                     "VIDEO_ID           INT    NOT NULL," \
                     "TIME           TEXT     NOT NULL," \
                     "LEN        CHAR(1) );";
    const char * sql3="CREATE TABLE VIDEO_INFO ("  \
                      "VIDEO_ID INTEGER PRIMARY KEY     NOT NULL," \
                      "NAME           TEXT    NOT NULL," \
                      "CHANL_ID          INT     NOT NULL," \
                      "TYPE_ID        INT NOT NULL,"\
                      "AREA_ID       INT NOT NULL  ,"\
                      "START_NUM INT NOT NULL ,"\
                      "PHOTO_URL   TEXT  ," \
                      "NET_URL  TEXT  NOT NULL );";
    exec(sql1,callback,this,&Errmsg);
    exec(sql2,callback,this,&Errmsg);
    exec(sql3,callback,this,&Errmsg);

}
char ** videoSqlite::m_exec( const char *sql,char **errmsg)
{
    mutex->Lock();
    if(exec(sql,callback,this,errmsg)!=SQLITE_OK)
    {
        mutex->unLock();
        return NULL;
    }else
    {
        mutex->unLock();
        return argv;
    }




}
int videoSqlite::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    videoSqlite *videoSql=(videoSqlite*)NotUsed;
    if(videoSql->argv!=NULL)
        free(videoSql->argv);
    videoSql->argv=(char **)malloc(sizeof(char *)*argc);
    if(videoSql->argv==NULL)
    {
        perror("videoSql->argv malloc error!");
        exit(1);
    }
    for(int i=0;i<argc;i++)
    {

        videoSql->argv[i]=(char *)malloc(strlen(argv[i]));
        if(videoSql->argv[i]==NULL)
        {
            perror("videoSql->argv[i] malloc error!");
            exit(1);
        }
        memcpy(videoSql->argv[i],argv[i],strlen(argv[i]));
    }
    videoSql->argc=argc;
    return 0;
}

int videoSqlite::Login(login_t *source,char **errmsg)
{
    char str[1024];
    sprintf(str,"SELECT * FROM USER WHERE NAME='%s' AND PASSWORD='%s';" ,source->username,source->psw);
    char **val=m_exec(str,errmsg);
    if(val!=NULL)
    {

        printf("登陆成功,user_id=%s\n",val[0]);
        return atoi(val[0]);
    }else{

        return -1;
    }
}



int videoSqlite::Register(myregister_t *source,char **errmsg)
{
    char str[1024];
    sprintf(str,"SELECT *  FROM USER WHERE NAME='%s';" ,source->username);
    if(m_exec(str,errmsg))
    {
        printf("BackServer:用户名重复！\n");
        return -1;
    }else{
        char id_s[6];
        srand(unsigned(time(NULL)));
        do
        {
            for(int i=0;i<6;i++)
            {
                if(!i)
                {
                    id_s[i]=rand()%9+'1';
                }else
                {
                    id_s[i]=rand()%10;
                }
                sprintf(str,"SELECT ID='%d' FROM USER;" ,atoi(id_s));

            }
        }while(m_exec(str,errmsg)!=NULL);  //生成随即数字  如果有重复重新来生成  （6位）
        int id=atoi(id_s);
        sprintf(str,"INSERT INTO USER "\
                    " (ID,NAME,PASSWORD,ONLINEFLAG) "  \
                    "VALUES (%d,'%s','%s',1); ",id,source->username,source->psw);
        m_exec(str,errmsg);
        if(errmsg==NULL)
        {
            return id;
        }else
        {
            return -1;
        }

    }
}




int videoSqlite::SendRequestList(sqlite3_callback fun ,void *data,char **errmsg)
{
    char str[1024];
    sprintf(str,"SELECT * FROM VIDEO_INFO;");
    mutex->Lock();
    int val= exec(str,fun,data,errmsg);
    mutex->unLock();
    return val;
}


