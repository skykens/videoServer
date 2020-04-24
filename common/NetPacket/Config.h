#ifndef CONFIG_H
#define CONFIG_H

#include <signal.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "../FrontServer/coreGui.h"
//这个类是用来全局配置的。包括配置前置进程和后置进程
//主要配置
// SIGPIPE SIGCHID 特定信号捕捉
// EPOLL监听数量  监听端口
// 线程池的初始线程  最大线程数
//通过读取为配置文件.
void signal_SIGPIPE(int );
void signal_SIGCHLD(int );
using namespace std;
class Config
{
public:
   static Config * ConfigInit();
   void bindSignal();
public:
   static Config * fig;
   bool gui=false;
   int default_threads;
    int max_threads;
    int max_listens;
    int port;
private:
    Config();



};

#endif // CONFIG_H
