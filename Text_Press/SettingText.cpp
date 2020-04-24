#include "SettingText.h"
//测试页面
SettingText::SettingText(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(400, 100, 720, 400);
    myconfig=new config_data;
    memset(myconfig,0,sizeof( config_data ) );
    UI_Init();
    connect(is_login_Button,SIGNAL(clicked()),this,SLOT(change_config()));
    connect(is_class_Button,SIGNAL(clicked()),this,SLOT(change_config()));
    connect(is_type_Button,SIGNAL(clicked()),this,SLOT(change_config()));
    connect(is_video_list_Button,SIGNAL(clicked()),this,SLOT(change_config()));
    connect(is_video_play_Button,SIGNAL(clicked()),this,SLOT(change_config()));
    connect(is_video_time_Button,SIGNAL(clicked()),this,SLOT(change_config()));
    connect(checkBox,SIGNAL(clicked()),this,SLOT(change_config()));
    connect(send_minute,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(change_config()));
    connect(client_sum,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(change_config()));
    connect(send_sec,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(change_config()));
    connect(pushButton_3,SIGNAL(pressed()),this,SLOT(close()));
    readconfig();
    change_config();
}

void SettingText::UI_Init()
{

    checkBox = new QCheckBox(this);
    checkBox->setText("是否处理应答");
    checkBox->setGeometry(QRect(400, 70, 150, 20));

    lab = new QLabel(this);
    lab->setText("测试时长(分钟):");
    lab->setGeometry(QRect(30, 70, 150, 25));

    lab2 = new QLabel(this);
    lab2->setText("客户端数量:");
    lab2->setGeometry(QRect(50, 120, 100, 20));

    lab3 = new QLabel(this);
    lab3->setText("发送间隔(毫秒):");
    lab3->setGeometry(QRect(360, 120, 130, 20));

    lab4 = new QLabel(this);
    lab4->setText("业务类型");
    lab4->setGeometry(QRect(300, 160, 100, 20));

    is_login_Button = new QCheckBox(this);
    is_login_Button->setText("用户登录");
    is_login_Button->setChecked(true);
    is_login_Button->setGeometry(QRect(100, 200, 150, 20));

    is_class_Button = new QCheckBox(this);
    is_class_Button->setText("获取视频频道列表");
    is_class_Button->setGeometry(QRect(300, 200, 180, 20));

    is_type_Button = new QCheckBox(this);
    is_type_Button->setText("获取视频类型列表");
    is_type_Button->setGeometry(QRect(100, 250, 180, 20));

    is_video_list_Button = new QCheckBox(this);
    is_video_list_Button->setText("获取视频列表");
    is_video_list_Button->setGeometry(QRect(300, 250, 170, 20));

    is_video_play_Button = new QCheckBox(this);
    is_video_play_Button->setText("上传点播记录");
    is_video_play_Button->setGeometry(QRect(500, 200, 150, 20));

    is_video_time_Button = new QCheckBox(this);
    is_video_time_Button->setText("上传点播时长记录");
    is_video_time_Button->setGeometry(QRect(500, 250, 180, 20));

    pushButton = new QPushButton(this);
    pushButton->setText("开始测试");
    pushButton->setGeometry(QRect(70, 320, 100, 23));

    pushButton_2 = new QPushButton(this);
    pushButton_2->setText("测试报告");
    pushButton_2->setGeometry(QRect(310, 320, 100, 23));

    pushButton_3 = new QPushButton(this);
    pushButton_3->setText("关闭");
    pushButton_3->setGeometry(QRect(520, 320, 100, 23));

    send_minute = new QLineEdit(this);
    send_minute->setGeometry(QRect(170, 70, 100, 20));

    client_sum = new QLineEdit(this);
    client_sum->setGeometry(QRect(170, 120, 100, 20));

    send_sec = new QLineEdit(this);
    send_sec->setGeometry(QRect(510, 120, 100, 20));
}


void SettingText::readconfig()
{
    QFile f("testconfig.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"SettingText提示","数据读取失败",QMessageBox::Yes);
    }
    QTextStream txtInput(&f);
    QString lineStr;
    int i=0;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        switch(i)
        {
            case 0:{
            send_minute->setText(lineStr);
            }break;
            case 1:{
            client_sum->setText(lineStr);
            }break;
            case 2:{
            send_sec->setText(lineStr);
            }break;
            case 3:
            {
                if(lineStr=="true")
                {
                    checkBox->setChecked(true);
                }
                else
                {
                    checkBox->setChecked(false);
                }
            }break;
            case 4:
            {
                if(lineStr=="true")
                    is_login_Button->setChecked(true);
                else
                    is_login_Button->setChecked(false);
            }break;
            case 5:
            {
                if(lineStr=="true")
                    is_class_Button->setChecked(true);
                else
                    is_class_Button->setChecked(false);
            }break;
            case 6:
            {
                if(lineStr=="true")
                    is_type_Button->setChecked(true);
                else
                    is_type_Button->setChecked(false);
            }break;
            case 7:
            {
                if(lineStr=="true")
                    is_video_list_Button->setChecked(true);
                else
                    is_video_list_Button->setChecked(false);
            }
            break;
            case 8:
            {
                if(lineStr=="true")
                    is_video_play_Button->setChecked(true);
                else
                    is_video_play_Button->setChecked(false);
            }break;
            case 9:
            {
                if(lineStr=="true")
                    is_video_time_Button->setChecked(true);
                else
                    is_video_time_Button->setChecked(false);
            }break;
            default:break;
        }
        i++;
    }
    f.close();
}

void SettingText::change_config()
{
    if(is_login_Button->isChecked())
    {
        this->myconfig->switch_Login = true;
    }
    else
    {
        this->myconfig->switch_Login = false;
    }
    if(is_class_Button->isChecked())
    {
        this->myconfig->switch_channel=true;
    }
    else
    {
        this->myconfig->switch_channel=false;
    }
    if(is_type_Button->isChecked())
    {
        this->myconfig->switch_type=true;
    }
    else
    {
        this->myconfig->switch_type=false;
    }
    if(is_video_list_Button->isChecked())
    {
        this->myconfig->switch_video_list=true;
    }
    else
    {
        this->myconfig->switch_video_list=false;
    }
    if(is_video_play_Button->isChecked())
    {
        this->myconfig->switch_video_play=true;
    }
    else
    {
        this->myconfig->switch_video_play=false;
    }
    if(is_video_time_Button->isChecked())
    {
        this->myconfig->switch_video_time=true;
    }
    else
    {
        this->myconfig->switch_video_time=false;
    }
    if(checkBox->isChecked())
    {
        this->myconfig->switch_answer=true;
    }
    else
    {
        this->myconfig->switch_answer=false;
    }
    this->myconfig->min_config=send_minute->text().toInt();
    this->myconfig->clint_num=client_sum->text().toInt();
    this->myconfig->sec_config=send_sec->text().toInt();
    saveconfig();
}


void SettingText::saveconfig()
{
    QFile f("testconfig.txt");
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"SettingText提示","数据保存失败",QMessageBox::Yes);
    }
    QTextStream txtOutput(&f);
    txtOutput << send_minute->text() << endl;
    txtOutput << client_sum->text() << endl;
    txtOutput << send_sec->text() << endl;
    if(checkBox->isChecked())
    {
        txtOutput << "true" << endl;
    }
    else
    {
        txtOutput << "false" << endl;
    }
    if(is_login_Button->isChecked())
    {
        txtOutput << "true" << endl;
    }
    else
    {
        txtOutput << "false" << endl;
    }
    if(is_class_Button->isChecked())
    {
        txtOutput << "true" << endl;
    }
    else
    {
        txtOutput << "false" << endl;
    }
    if(is_type_Button->isChecked())
    {
        txtOutput << "true" << endl;
    }
    else
    {
        txtOutput << "false" << endl;
    }
    if(is_video_list_Button->isChecked())
    {
        txtOutput << "true" << endl;
    }
    else
    {
        txtOutput << "false" << endl;
    }
    if(is_video_play_Button->isChecked())
    {
        txtOutput << "true" << endl;
    }
    else
    {
        txtOutput << "false" << endl;
    }
    if(is_video_time_Button->isChecked())
    {
        txtOutput << "true" << endl;
    }
    else
    {
        txtOutput << "false" << endl;
    }
    f.close();
}

void SettingText::writelog()
{
//    QString str="business/";
//    str+=QDateTime::currentDateTime().toString("yyyy-MM-dd");
//    str+=".txt";
//    QFile f(str);
//    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
//    {
//        QMessageBox::information(this,"SettingText提示","数据保存失败",QMessageBox::Yes);
//    }
//    QTextStream txtOutput(&f);
//    txtOutput.setCodec(QTextCodec::codecForName("UTF-8"));
//    QByteArray *temp=new QByteArray;
//     if(this->myconfig->switch_Login)
//     {
//         str="功能：登陆";
//         txtOutput << str<<endl;
//         str="类型：发送";
//         txtOutput << str<<endl;
//         str="用户ID：admin";
//         txtOutput << str<<endl;
//         PacketBase *loginPag=factory.CreateLogin();
//         for(int j=0;j<128;j++)
//         {
//             for(int i=0;i<16;i++)
//             {
//                 temp->push_back(loginPag.getData()[i+j*16]);
//             }
//             txtOutput<<temp->toHex()<<endl;
//             temp->clear();
//         }
//     }
//     if(this->myconfig->switch_video_list)
//     {
//         str="功能：获取视频列表";
//         txtOutput << str<<endl;
//         str="类型：发送";
//         txtOutput << str<<endl;
//         str="用户ID：admin";
//         txtOutput << str<<endl;
//        BusyPacket get_channel_list_Pag(3);
//        for(int j=0;j<128;j++)
//        {
//            for(int i=0;i<16;i++)
//            {
//                temp->push_back(get_channel_list_Pag.getData()[i+j*16]);
//            }
//            txtOutput<<temp->toHex()<<endl;
//            temp->clear();
//        }
//     }
//     if(this->myconfig->switch_channel)
//     {
//         str="功能：获取频道";
//         txtOutput << str<<endl;
//         str="类型：发送";
//         txtOutput << str<<endl;
//         str="用户ID：admin";
//         txtOutput << str<<endl;
//         BusyPacket get_video_type_Pag(4);
//         for(int j=0;j<128;j++)
//         {
//             for(int i=0;i<16;i++)
//             {
//                 temp->push_back(get_video_type_Pag.getData()[i+j*16]);
//             }
//             txtOutput<<temp->toHex()<<endl;
//             temp->clear();
//         }
//     }
//     if(this->myconfig->switch_type)
//     {
//         str="功能：获取视频类型";
//         txtOutput << str<<endl;
//         str="类型：发送";
//         txtOutput << str<<endl;
//         str="用户ID：admin";
//         txtOutput << str<<endl;
//         BusyPacket get_video_list_Pag(6);
//         for(int j=0;j<128;j++)
//         {
//             for(int i=0;i<16;i++)
//             {
//                 temp->push_back(get_video_list_Pag.getData()[i+j*16]);
//             }
//             txtOutput<<temp->toHex()<<endl;
//             temp->clear();
//         }
//     }
//     if(this->myconfig->switch_video_play)
//     {
//         str="功能：上传视频点播记录";
//         txtOutput << str<<endl;
//         str="类型：发送";
//         txtOutput << str<<endl;
//         str="用户ID：admin";
//         txtOutput << str<<endl;
//         BusyPacket upload_record_Pag(9);
//         for(int j=0;j<128;j++)
//         {
//             for(int i=0;i<16;i++)
//             {
//                 temp->push_back(upload_record_Pag.getData()[i+j*16]);
//             }
//             txtOutput<<temp->toHex()<<endl;
//             temp->clear();
//         }
//     }
//     if(this->myconfig->switch_video_time)
//     {
//         str="功能：上次点播时长";
//         txtOutput << str<<endl;
//         str="类型：发送";
//         txtOutput << str<<endl;
//         str="用户ID：admin";
//         txtOutput << str<<endl;
//         BusyPacket upload_time_length_Pag(10);
//         for(int j=0;j<128;j++)
//         {
//             for(int i=0;i<16;i++)
//             {
//                 temp->push_back(upload_time_length_Pag.getData()[i+j*16]);
//             }
//             txtOutput<<temp->toHex()<<endl;
//             temp->clear();
//         }
//     }
}
