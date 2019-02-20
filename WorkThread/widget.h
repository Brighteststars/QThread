#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QThread>
class QProgressBar;
#include"workthread.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    //���½���
    void handleResults(int value);


    //��ʼ�߳�
    void startThread();

private:
    QProgressBar* m_pProgressBar;

    WorkThread* m_workThread;

};

#endif // WIDGET_H
