/*************************************************************************
	> File Name: SqliteBase.h
	> Author: 
	> Mail: 
	> Created Time: 2019年10月26日 星期六 16时14分17秒
 ************************************************************************/

#ifndef _SQLITEBASE_H
#define _SQLITEBASE_H
//#include "SqliteBase.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

class SqliteBase
{

    public:
        SqliteBase(const char *filename);
        ~SqliteBase();
       int open();
       virtual int exec(const char *sql,sqlite3_callback fun,void *data,char **errmsg);
       int close();
    protected:
       const char * name;
       virtual void createTable()=0;
       sqlite3 *db;


};
#endif
