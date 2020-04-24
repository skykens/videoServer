/**
 * Project Untitled
 */


#include "LogSystem.h"
LogSystem::LogSystem()
{




}
LogSystem::~LogSystem()
{

}
void LogSystem::addLogger(LogBase *target)
{
    log_vect.push_back(target);
    return;
}
