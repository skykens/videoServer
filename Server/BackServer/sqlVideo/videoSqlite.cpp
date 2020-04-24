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
    createTable();

}
void videoSqlite::createTable()
{
    char *Errmsg=0;
    const char *sql1="CREATE TABLE USER ("  \
                     "ID INTEGER PRIMARY KEY ," \
                     "NAME           TEXT    NOT NULL," \
                     "PASSWORD       TEXT    NOT NULL,"
                     "QUESTION       TEXT    NOT NULL,"
                     "ANSWER         TEXT    NOT NULL );";

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
char ** videoSqlite::m_exec( const char *sql)
{
     char **tmperr;
    if(exec(sql,callback,this,tmperr)!=SQLITE_OK)
    {
        perror(*tmperr);
        return NULL;
    }else
    {
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
const char * videoSqlite::Errormsg()
{
    return errmsg;
}
int videoSqlite::Login(login &src)
{
    char str[1024];
    sprintf(str,"SELECT ID FROM USER WHERE NAME='%s' AND PASSWORD='%s';",src.data.name(),src.data.psw());
    char **val=m_exec(str);
    if(val!=NULL)
    {
        return atoi(argv[0]);
    }else{
        strcpy(errmsg,"username or password error.");
        return -1;
    }
}
int videoSqlite::Register(regist &src)
{
    char str[1024];
    sprintf(str,"SELECT *  FROM USER WHERE NAME='%s';" ,src.data.name().c_str());
    if(m_exec(str))
    {
        strcpy(errmsg,"Name has been registered.");
        return -1;
    }else{
        char id_s[6];
        srand(unsigned(time(NULL)));
        do
        {
            for(int i=0;i<6;i++)
            {
                if(i==0)
                {
                    id_s[i]=rand()%9+'1';  //第一个数字不能为0
                }else
                {
                    id_s[i]=rand()%10;
                }
                sprintf(str,"SELECT ID='%d' FROM USER;" ,atoi(id_s));

            }
        }while(m_exec(str)!=NULL);  //生成随即数字  如果有重复重新来生成  （6位）
        int id=atoi(id_s);
        sprintf(str,"INSERT INTO USER "\
                    " (ID,NAME,PASSWORD,QUESTION,ANSWER) "  \
                    "VALUES (%d,'%s','%s','%s','%s'); ",id,src.data.name().c_str(),src.data.psw().c_str(),
                     src.data.psw_question().c_str(),src.data.psw_answer().c_str());
        if(m_exec(str)!=NULL)
        {
            return id;
        }else
        {
            strcpy(errmsg,"Please check your network.");
            return -1;
        }

    }
}
char **videoSqlite::videoList()
{
    return m_exec("SELECT * FROM VIDEO_INFO;");
}


