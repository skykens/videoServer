#ifndef SETTINGTEXT_H
#define SETTINGTEXT_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QTextCodec>
#include <QtWidgets/QMessageBox>
#include "../common/NetPacket/NetPacket.h"

class SettingText : public QWidget
{
    Q_OBJECT
public:
    explicit SettingText(QWidget *parent = 0);
    QCheckBox *checkBox;
    QLabel *lab;
    QLabel *lab2;
    QLabel *lab3;
    QLabel *lab4;
    QCheckBox *is_login_Button;
    QCheckBox *is_class_Button;
    QCheckBox *is_type_Button;
    QCheckBox *is_video_list_Button;
    QCheckBox *is_video_play_Button;
    QCheckBox *is_video_time_Button;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLineEdit *send_minute;
    QLineEdit *client_sum;
    QLineEdit *send_sec;
    config_data_t *myconfig;
    void UI_Init();
    void readconfig();//从文件读配置到界面
    void saveconfig();//从界面读配置保存文件
    void writelog();//写日志
signals:

public slots:
    void change_config();
private:
};

#endif // SETTINGTEXT_H
