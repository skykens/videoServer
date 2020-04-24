/**
 * Project Untitled
 */


#ifndef _LOGBASE_H
#define _LOGBASE_H
#include <log4cplus/log4cplus.h>
#include <iostream>
#include <string>

using namespace log4cplus;
class LogBase {
public: 
     LogBase(std::string);
     virtual ~LogBase();
    void addFileAppender(std::string);
    void addConsoleAppender(std::string);
    inline void InfoLog_out(std::string info){
        LOG4CPLUS_INFO(log_handler, LOG4CPLUS_TEXT(info));
    }
    inline void ErrorLog_out(std::string error){
        LOG4CPLUS_WARN(log_handler, LOG4CPLUS_TEXT(error));

    }
private:
    void init();
protected: 
    Logger log_handler;
    std::string log_name;

};

#endif //_LOGBASE_H
