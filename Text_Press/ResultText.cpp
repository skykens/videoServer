#include "ResultText.h"

ResultText::ResultText(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(400,300,400,300);
    mytext=new QTextEdit(this);
    mytext->setGeometry(0,0,400,300);
    readdate();
    time=new QTimer;
    connect(time,SIGNAL(timeout()),this,SLOT(readdate()));
    time->start(3000);
}

void ResultText::readdate()
{
    QString filename="RealTimeLog/";
    filename+=QDateTime::currentDateTime().toString("yyyy-MM-dd");
    filename+="RealTimeLog.txt";
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"ResultText提示","数据保存失败",QMessageBox::Yes);
    }
    QTextStream txtOutput(&f);
    QString str;
    while(!txtOutput.atEnd())
    {
        str+= txtOutput.readLine();
        str+='\n';
    }
    f.close();
    mytext->setText(str);
}
