#ifndef FUN_CONNECT_H
#define FUN_CONNECT_H

#include <QtWidgets>
#include "loginwidget.h"
#include<QtNetwork/QTcpSocket>
#include<QtNetwork/QHostAddress>
#include<QtWidgets/QMessageBox>
#include <QString>
#include "ResultText.h"
#include "SettingText.h"
#include "Texting.h"

class Fun_connect : public QWidget
{
    Q_OBJECT

public:
    explicit Fun_connect(QWidget *parent = 0);
    char net_ip[20];
    QString net_port;
    CHostAddress myaddr;

    QTcpSocket *Socket;
    config_data_t *myconfig;

    void ConnectNet();//
    void StressConfig();//
    void newTexting();//
protected:
    void StartLog();//
    void resultshow();//
    ResultText *myresult;//
    Texting *myTestGui;//
    SettingText *myConfigGui;//
    LoginWidget *myNet;//

public slots:
    void go_report();
    void stressconfig_Go_Texting();
    void Texting_Go_stressconfig();
    void go_Connect();

};

#endif // FUN_CONNECT_H
