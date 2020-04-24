#include "Config.h"
Config * Config::fig=NULL;
Config* Config::ConfigInit()
{
    if(!fig)
        fig=new Config();
    return fig;
}
Config::Config()
{
    ifstream read_file;
    read_file.open("config.conf", ios::binary);
    string line;
    int count=4;
    while(getline(read_file, line))
    {
        long num=line.find('=');
        if(line.substr(0,num)=="default_threads")
        {
            default_threads=atoi(line.substr(num+1).c_str());
            count--;
        }else if(line.substr(0,num)=="max_threads")
            {
            max_threads=atoi(line.substr(num+1).c_str());
            count--;
            }else if(line.substr(0,num)=="max_listens")
            {
            max_listens=atoi(line.substr(num+1).c_str());
            count--;
            }else if(line.substr(0,num)=="port")
            {
            port=atoi(line.substr(num+1).c_str());
            count--;
        }else if(line.find("gui_start")!=-1)
        {
            coreGui::initGui();
            coreGui::clrScreen();

        }

    }

    if(count)
     {
        cout<<"config init fail! Please check config.conf"<<endl;
        exit(0);
    }

    if(default_threads<=0||default_threads>=max_threads)
        default_threads=1;
    if(max_threads>100||max_threads<=default_threads)
        max_threads=50;
    if(max_listens<=100||max_listens>10000000)
        max_listens=100000;


    bindSignal();


}

void Config::bindSignal()
{
    signal(SIGPIPE,signal_SIGPIPE);
    signal(SIGCHLD,signal_SIGCHLD);

}

void signal_SIGPIPE(int sig)
{







}
void signal_SIGCHLD(int sig)
{

}





