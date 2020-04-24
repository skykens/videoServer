
#include "LogBase.h"
LogBase::LogBase(std::string name):log_name(name)
{
    init();
}
LogBase::~LogBase()
{

}

void LogBase::addFileAppender(std::string filename) {


    SharedAppenderPtr fileAppender(new FileAppender(
                                       LOG4CPLUS_TEXT(filename),
                                       std::ios_base::app
                                       )
                                   );
    fileAppender->setName(LOG4CPLUS_TEXT(filename));
    tstring pattern = LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S,%Q} - %m %n");
    fileAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(pattern)));

    log_handler.addAppender(fileAppender);

    return;
}

void LogBase::addConsoleAppender(std::string Name) {
    SharedAppenderPtr consoleAppender(new log4cplus::ConsoleAppender);
    consoleAppender->setName(LOG4CPLUS_TEXT(Name));
    consoleAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::SimpleLayout()));
    log_handler.addAppender(consoleAppender);
    return;
}
void LogBase::init() {

  //  Initializer initializer;

    log_handler = Logger::getInstance(LOG4CPLUS_TEXT (log_name));
    log_handler.setLogLevel(log4cplus::INFO_LOG_LEVEL);

    return;
}
