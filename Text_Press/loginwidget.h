#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QtWidgets/QMessageBox>
/*********连网络页面**********/
class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);

    QLabel *lab_ip;
    QLabel *lab_port;
    QLineEdit *edit_ip;
    QLineEdit *edit_port;
    QPushButton *btn_link;
    QTextStream *myfile;
    void Read_Net();//将输入的ip和端口存到文件里
    void Save_Net();//将文件里的最新ip和端口读出来并写在控件上面
signals:

public slots:

private:
    void UI_init();
};

#endif // LOGINWIDGET_H
