#include "fun_connect.h"

Fun_connect::Fun_connect(QWidget *parent)
    : QWidget(parent)
{
    this->setGeometry(0,0,0,0);
    this->ConnectNet();
    memcpy(net_ip,"127.0.0.1",9);
    net_port = "6666";
    Socket = new QTcpSocket;
    myconfig = new config_data_t;
    memset(myconfig,0,sizeof(config_data_t));
}

void Fun_connect::ConnectNet()//连接ip和prot
{
    myNet = new LoginWidget; 
    myNet->show();//show出连接ip和端口的页面
    connect(myNet->btn_link,SIGNAL(pressed()),this,SLOT(go_Connect()));//用信号槽连接到下一个页面
}

void Fun_connect::go_Connect()
{
    myNet->Save_Net();//发送ip和端口
    Socket->connectToHost(myNet->edit_ip->text(),myNet->edit_port->text().toInt());
    if(Socket->waitForConnected(3000))//等待3秒
    {
        StartLog();
        myaddr.SetIp(myNet->edit_ip->text().toStdString().c_str());
        myaddr.SetPort(myNet->edit_port->text().toUInt());
        QMessageBox::information(this->myNet,"提示","连接成功",QMessageBox::Yes);
        delete myNet;
        return StressConfig();//连接成功之后就打开设置页面
    }
    else
    {
        QMessageBox::information(this->myNet,"提示","连接失败\n超时或错误",QMessageBox::Yes);
    }
//    delete myNet;
//    return StressConfig();
}

void Fun_connect::StartLog()//将写入的ip和端口存到StartLog.txt文档中
{
     QString str="StartLog/";
     str+=QDateTime::currentDateTime().toString("yyyy-MM-dd");
     str+="StartLog.txt";
     QFile f(str);
     if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
     {
         QMessageBox::information(this,"Fun_connect提示","数据写入失败",QMessageBox::Yes);
     }
     else
     {
         QTextStream txtOutput(&f);
         QString str;
         char buf[2048]="";
         sprintf(buf,"有效启动时间");
         str=buf;
         str+=QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
         txtOutput << str<<endl;
         str="功能：连接";
         txtOutput << str<<endl;
         str="类型：发送";
         txtOutput << str<<endl;
         str="用户ID：admin";
         txtOutput << str<<endl;
     }
     f.close();
}

void Fun_connect::StressConfig()//参数配置界面
{
    myConfigGui=new SettingText;
    myConfigGui->show();
    connect(myConfigGui->pushButton,SIGNAL(pressed()),this,SLOT(stressconfig_Go_Texting()));
    connect(myConfigGui->pushButton_2,SIGNAL(pressed()),this,SLOT(go_report()));
}

void Fun_connect::newTexting()//测试界面
{
    myTestGui=new Texting(this->myconfig,myaddr);
    myTestGui->show();
    connect(myTestGui->pushButton,SIGNAL(pressed()),this,SLOT(Texting_Go_stressconfig()));
    connect(myTestGui->pushButton_2,SIGNAL(pressed()),this,SLOT(go_report()));
}

void Fun_connect::resultshow()
{
    myresult=new ResultText;
    myresult->show();
}

void Fun_connect::go_report()
{
    return resultshow();
}

void Fun_connect::stressconfig_Go_Texting()
{
    myConfigGui->writelog();
    memcpy(this->myconfig,myConfigGui->myconfig,sizeof(config_data));
    delete myConfigGui;
    return this->newTexting();
}

void Fun_connect::Texting_Go_stressconfig()
{
    myTestGui->myEpollClient->myEpollClient->SetTimeout(0);
    myTestGui->myEpollClient->myEpollClient->Stop();
    delete myTestGui;
    return this->StressConfig();
}

