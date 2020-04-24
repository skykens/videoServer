#ifndef RESULTTEXT_H
#define RESULTTEXT_H

#include <QtWidgets/QWidget>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDateTime>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTextEdit>
#include <QTimer>

class ResultText : public QWidget
{
    Q_OBJECT
public:
    explicit ResultText(QWidget *parent = 0);
    QTextEdit *mytext;
    QTimer *time;

signals:

public slots:
    void readdate();//按日期读取最近一次测试数据
};

#endif // RESULTTEXT_H
