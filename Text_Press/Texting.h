#ifndef TEXTING_H
#define TEXTING_H
#include <unordered_set>
#include <QtWidgets/QWidget>
#include <QtNetwork/QtNetwork>
#include <QThreadPool>
#include <QThread>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QString>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QtWidgets/QMessageBox>
#include "../common/NetPacket/PacketBase.h"
#include "../common/NetPacket/NetPacket.h"
#include "TaskEpoll.h"

class Texting : public QWidget
{
    Q_OBJECT
public:
    explicit Texting(config_data *myconfig,CHostAddress myaddr);
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTimer *send_test;//定时器1
    QTimer *test_duration;//定时器1
    config_data *myconfig;//配置界面所有参数
    int send_pag_sum;//发送所有包的数量
    int send_pag_sucess_sum;//所有发送成功包的数量
    int send_pag_fail_sum;//所有发送失败包的数量
    int testing;//剩余还未测试的时间(秒)
    int tested;//以测试完的时间(秒)
    QThreadPool *mypool;//线程池
    TaskEpoll *myEpollClient;//epoll管理所有fd模块任务
    ~Texting();
    clientPacket::keepactive *hreat;//心跳包
    clientPacket::login *loginPag;//登陆包
    int send_login_Pag_sum;//发送登陆包数
    PacketBase *get_channel_list_Pag;//获取频道列表包
    int send_get_channel_list_Pag_Pagsum;//发送获取频道列表包数
    PacketBase *get_video_type_Pag;//获取视频类型包
    int send_get_video_type_Pag_sum;//发送获取视频类型包数
    PacketBase *get_video_list_Pag;//获取视频列表包
    int send_get_video_list_Pag_sum;//发送视频列表包数
    PacketBase *upload_record_Pag;//上传点播记录包
    int send_upload_record_Pag_sum;//发送上传点播记录包数
    PacketBase *upload_time_length_Pag;//上传点播时长包
    int send_upload_time_length_Pag_sum;//发送上传点播时长包数
    void log_now();//
signals:

public slots:
    void text_show();
    void sendMsg();
    void testing_time_show();
};

#endif // TEXTING_H
