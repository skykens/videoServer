#include "loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent)
{
    UI_init();
    Read_Net();
//    Save_Net();
}

void LoginWidget::UI_init()
{
    this->setGeometry(500,100,500,200);
    lab_ip = new QLabel(this);
    lab_ip->setText("IP:");
    lab_ip->setGeometry(QRect(50, 50, 60, 20));

    lab_port = new QLabel(this);
    lab_port->setText("PORT:");
    lab_port->setGeometry(QRect(260, 50, 60, 20));

    edit_ip = new QLineEdit(this);
    edit_ip->setGeometry(QRect(80, 45, 150, 30));

    edit_port = new QLineEdit(this);
    edit_port->setGeometry(QRect(310, 45, 150, 30));

    btn_link = new QPushButton(this);
    btn_link->setText(("连接网络"));
    btn_link->setGeometry(QRect(200, 130, 100, 30));
}

void LoginWidget::Read_Net()
{
    QFile file("NetConfig.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"LoginWidget提示","数据读取失败",QMessageBox::Yes);
    }
    QTextStream txtInput(&file);
    QString lineStr;
    int i=0;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        switch(i)
        {
            case 0:
            {
                edit_ip->setText(lineStr);
            }
                break;
            case 1:
            {
                edit_port->setText(lineStr);
            }
                break;
            default:
                break;
        }
        i++;
    }
    file.close();
}

void LoginWidget::Save_Net()
{
    QFile file("NetConfig.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"LoginWidget提示","数据保存失败",QMessageBox::Yes);
    }
    QTextStream txtOutput(&file);
    txtOutput << edit_ip->text() << endl;
    txtOutput << edit_port->text() << endl;
    file.close();
}
