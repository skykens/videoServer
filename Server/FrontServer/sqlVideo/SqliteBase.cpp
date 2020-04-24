/*************************************************************************
	> File Name: SqliteBase.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年10月26日 星期六 16时14分16秒
 ************************************************************************/

#include "SqliteBase.h"
SqliteBase::SqliteBase(const char *filename)
    :name(filename)
{
    int rc;
    rc=open();
    if(rc)
    {
        fprintf(stderr,"Can't open database :%s\n",sqlite3_errmsg(db));
        exit(0);
    }
}

int SqliteBase::exec(const char *sql,sqlite3_callback fun,void *data,char **errmsg)
{
    int rc;
    rc=sqlite3_exec(db,sql,fun,data,errmsg);
    if(rc!=SQLITE_OK)
    {
        fprintf(stderr,"SQL error :%s\n",*errmsg);
       // sqlite3_free(errmsg);
    }
    return rc;



}
int SqliteBase::open()
{
    return sqlite3_open(name,&db);
}
int SqliteBase::close()
{
    sqlite3_close(db);
}
SqliteBase::~SqliteBase()
{
    close();
}
