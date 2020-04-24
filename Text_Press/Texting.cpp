#include "Texting.h"

Texting::Texting(config_data *myconfig,CHostAddress myaddr)
{
    int size=0;
    char *src=NULL;
    this->setGeometry(400, 100,600, 320);
    /*******************业务包打包*********************************/


    loginPag=new clientPacket::login();
    loginPag->data.set_name("admin");
    loginPag->data.set_psw("123123");
    //get_channel_list_Pag=factory.;
//    get_video_type_Pag=factory.CreateVideoType();
//    get_video_list_Pag=factory.CreateVideoList();
//    upload_record_Pag=factory.;
//    upload_time_length_Pag=
    hreat=new clientPacket::keepactive();
    /*******************测试参数传递和配置*******************************/
    this->myconfig=new config_data;
    memset(this->myconfig,0,sizeof( config_data ) );
    memcpy(this->myconfig,myconfig,sizeof( config_data) );
    send_pag_sum=0;
    send_pag_sucess_sum=0;
    send_pag_fail_sum=0;
    tested=0;
    testing=this->myconfig->min_config*60;
    send_login_Pag_sum=0;
    send_get_channel_list_Pag_Pagsum=0;
    send_get_video_type_Pag_sum=0;
    send_get_video_list_Pag_sum=0;
    send_upload_record_Pag_sum=0;
    send_upload_time_length_Pag_sum=0;
    /**************************************************/
    char buf[10]="";
    QString str;
    /**************************************************/
    label = new QLabel(this);
    label->setText("测试时长(分钟):");
    label->setGeometry(QRect(15, 40, 145, 20));
    label_2 = new QLabel(this);
    label_2->setText("模拟客户端数");
    label_2->setGeometry(QRect(200, 40, 115, 20));
    label_3 = new QLabel(this);
    label_3->setText("发送间隔(毫秒)");
    label_3->setGeometry(QRect(390, 40, 125, 20));
    /*******************显示测试参数控件*******************************/
    lineEdit_9 = new QLineEdit(this);
    lineEdit_9->setGeometry(QRect(140, 40, 50, 20));
    sprintf(buf,"%d",this->myconfig->min_config);
    str=buf;
    lineEdit_9->setText(str);
    lineEdit_10 = new QLineEdit(this);
    lineEdit_10->setGeometry(QRect(320, 40, 50, 20));
    sprintf(buf,"%d",this->myconfig->clint_num);
    str=buf;
    lineEdit_10->setText(str);
    lineEdit_11 = new QLineEdit(this);
    lineEdit_11->setGeometry(QRect(520, 40, 70, 20));
    sprintf(buf,"%d",this->myconfig->sec_config);
    str=buf;
    lineEdit_11->setText(str);
    /********************显示实时测试数据控件******************************/
    label_4 = new QLabel(this);
    label_4->setText("发起连接数:");
    label_4->setGeometry(QRect(40, 100, 110, 20));
    lineEdit = new QLineEdit(this);
    lineEdit->setGeometry(QRect(140, 100, 113, 20));
    label_5 = new QLabel(this);
    label_5->setText("已测试时间(秒):");
    label_5->setGeometry(QRect(15, 140, 125, 20));
    lineEdit_2 = new QLineEdit(this);
    lineEdit_2->setGeometry(QRect(140, 140, 113, 20));
    label_6 = new QLabel(this);
    label_6->setText("发送请求包:");
    label_6->setGeometry(QRect(40, 180, 110, 20));
    lineEdit_3 = new QLineEdit(this);
    lineEdit_3->setGeometry(QRect(140, 180, 113, 20));
    label_7 = new QLabel(this);
    label_7->setText("上传成功:");
    label_7->setGeometry(QRect(40, 220, 100, 20));
    lineEdit_4 = new QLineEdit(this);
    lineEdit_4->setGeometry(QRect(140, 220, 113, 20));
    /**********************显示实时测试数据控件****************************/
    label_8 = new QLabel(this);
    label_8->setText("成功登陆:");
    label_8->setGeometry(QRect(360, 100, 80, 20));
    lineEdit_8 = new QLineEdit(this);
    lineEdit_8->setGeometry(QRect(460, 100, 113, 20));
    label_9 = new QLabel(this);
    label_9->setText("剩余时间(秒):");
    label_9->setGeometry(QRect(340, 140, 110, 20));
    lineEdit_5 = new QLineEdit(this);
    lineEdit_5->setGeometry(QRect(460, 140, 113, 20));
    label_10 = new QLabel(this);
    label_10->setText("收到应答包:");
    label_10->setGeometry(QRect(360, 220, 110, 20));
    lineEdit_6 = new QLineEdit(this);
    lineEdit_6->setGeometry(QRect(460, 180, 113, 20));
    label_11 = new QLabel(this);
    label_11->setText("上传失败:");
    label_11->setGeometry(QRect(360, 180, 80, 20));
    lineEdit_7 = new QLineEdit(this);
    lineEdit_7->setGeometry(QRect(460, 220, 113, 20));
    /*********************按钮*****************************/
    pushButton = new QPushButton(this);
    pushButton->setText("停止测试");
    pushButton->setGeometry(QRect(120, 280, 75, 23));
    pushButton_2 = new QPushButton(this);
    pushButton_2->setText("测试报告");
    pushButton_2->setGeometry(QRect(370, 280, 75, 23));
    /*********************线程池和线程*****************************/
    mypool=new QThreadPool;
//    mythread=new QThread;
    /********************线程池添加客户端epoll管理模型任务**************************/
    myEpollClient=new TaskEpoll(this->myconfig->clint_num, myaddr);
    mypool->start(( QRunnable* )myEpollClient);
//    mythread->thread()
    /********************定时器**************************/
    send_test=new QTimer(this);
    connect(send_test,SIGNAL(timeout()),this,SLOT(sendMsg()));
    //////////
    test_duration=new QTimer(this);
    connect(test_duration,SIGNAL(timeout()),this,SLOT(testing_time_show()));
    connect(test_duration,SIGNAL(timeout()),this,SLOT(text_show()));
   test_duration->start(1000);
//     this->log_now();
}
Texting::~Texting()
{
    delete  myEpollClient->myEpollClient;
}

void Texting::log_now()
{
    QString str="RealTimeLog/";
    str+=QDateTime::currentDateTime().toString("yyyy-MM-dd");
    str+="RealTimeLog.txt";
    QFile f(str);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"Texting提示","数据写入失败",QMessageBox::Yes);
    }
    else
    {
        QTextStream txtOutput(&f);
        txtOutput.setCodec( QTextCodec::codecForName("UTF-8"));
        char buf[MAX_PACKET]="";
        sprintf(buf,"有效连接数： %d;",myEpollClient->myEpollClient->connectSucces);
        str=buf;
        txtOutput << str<<endl;

        sprintf(buf,"接收数据包： %d; 发送数据包：%d;以测试时间%d(秒)",myEpollClient->myEpollClient->RecvSum,send_pag_sucess_sum,tested);
        str=buf;
        txtOutput << str<<endl;

        sprintf(buf,"用户登陆数： %d; 获取视频频道：%d; 获取视频分类：%d;",send_login_Pag_sum,send_get_channel_list_Pag_Pagsum,send_get_video_type_Pag_sum);
        str=buf;
        txtOutput << str<<endl;

        sprintf(buf,"获取视频列表： %d; 上传播放数据：%d; 上传播放时长：%d;",send_get_video_list_Pag_sum,send_upload_record_Pag_sum,send_upload_time_length_Pag_sum);
        str=buf;
        txtOutput << str<<endl;

        sprintf(buf,"不完整包数：%d;",myEpollClient->myEpollClient->RecvSumFail);
        str=buf;
        txtOutput << str<<endl;
    }
    f.close();
}

void Texting::text_show()//更新界面数据
{
    QString str=QString::number(testing);//剩余时间
    lineEdit_5->setText(str);
    str=QString::number(tested);//以测试完时间
    lineEdit_2->setText(str);
    str=QString::number(myconfig->clint_num);//模拟客户端发起连接数
    lineEdit->setText(str);
    str=QString::number(myEpollClient->myEpollClient->connectSucces);//模拟客户端发起连接成功数
    lineEdit_8->setText(str);
    str=QString::number(myEpollClient->myEpollClient->RecvSum);//收到应答包数
    lineEdit_7->setText(str);
    str=QString::number(send_pag_fail_sum);//上传失败次数 myTaskWrite::sendFailSum
    lineEdit_6->setText(str);
    str=QString::number(send_pag_sucess_sum);//上传成功次数
    lineEdit_4->setText(str);
    str=QString::number(send_pag_sum);//发送请求包次数
    lineEdit_3->setText(str);
    this->log_now();
}
void Texting::sendMsg()
{
    char src[MAX_PACKET];
    int packsz=0;
    for(int fd : myEpollClient->myEpollClient->client_fd)
    {
//       write(fd,hreat->getData(),MAX_PACKET);
       if(this->myconfig->switch_Login)
       {
           packsz=loginPag->SerializeToArray(src,MAX_PACKET);

           int size=write(fd,src,packsz);
           if(size!=packsz)
           {
               send_pag_fail_sum++;

           }else
           {
               send_pag_sucess_sum++;
               send_login_Pag_sum++;


           }
           send_pag_sum++;
        }
//        if(this->myconfig->switch_video_list)
//        {
//           int size=write(fd,get_video_list_Pag->Tochar(),get_video_list_Pag->size());
//            if(size==get_video_list_Pag->size())
//            {
//                send_pag_sucess_sum++;
//                send_get_video_list_Pag_sum++;
//            }
//            else
//            {
//                send_pag_fail_sum++;
//            }
//            send_pag_sum++;
//        }
//        if(this->myconfig->switch_channel)
//        {
//            int size=write(fd,get_channel_list_Pag->getData(),MAX_PACKET);
//            if(size==MAX_PACKET)
//            {
//                send_pag_sucess_sum++;
//                send_get_channel_list_Pag_Pagsum++;
//            }
//            else
//            {
//                send_pag_fail_sum++;
//            }
//            send_pag_sum++;
//        }
//        if(this->myconfig->switch_type)
//        {
//            int size=write(fd,get_video_type_Pag->Tochar(),get_video_list_Pag->size());
//            if(size==get_video_list_Pag->size())
//            {
//                send_pag_sucess_sum++;
//                send_get_video_type_Pag_sum++;
//            }
//            else
//            {
//                send_pag_fail_sum++;
//            }
//            send_pag_sum++;
//        }
//        if(this->myconfig->switch_video_play)
//        {
//            int size=write(fd,upload_record_Pag->getData(),MAX_PACKET);
//            if(size==MAX_PACKET)
//            {
//                send_pag_sucess_sum++;
//                send_upload_record_Pag_sum++;
//            }
//            else
//            {
//                send_pag_fail_sum++;
//            }
//            send_pag_sum++;
//        }
//        if(this->myconfig->switch_video_time)
//        {
//            int size=write(fd,upload_time_length_Pag->getData(),MAX_PACKET);
//            if(size==MAX_PACKET)
//            {
//                send_pag_sucess_sum++;
//                send_upload_time_length_Pag_sum++;
//            }
//            else
//            {
//                send_pag_fail_sum++;
//            }
//            send_pag_sum++;
//        }
    }
}

void Texting::testing_time_show()  //测试时间更新
{
    if(testing==this->myconfig->min_config*60)
    {
        send_test->start(this->myconfig->sec_config);
        myEpollClient->myEpollClient->startNewConnect();
        testing--;
        tested++;
    }
    else if(testing==0)
    {
        send_test->stop();
        test_duration->stop();
    }
    else
    {
        testing--;
        tested++;
    }
}
