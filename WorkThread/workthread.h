#ifndef WORKTHREAD_H
#define WORKTHREAD_H
#include <QThread>
#include <QDebug>


class WorkThread:public QThread
{
    Q_OBJECT
public:
    explicit WorkThread(QObject* parent = 0):QThread(parent)
    {
        //�����߳��Ϲ�����WorkThread
        qDebug() << "Worker Thread: " << QThread::currentThreadId();
    }

    ~WorkThread()
    {
        //��ֹ���̷߳��ʹ�����Դʱ,���̵߳���run()�ڷ��ʹ�����Դ,�����ж����߳�
//        requestInterruption();

        //���̵߳�����������ʱ,������������,ֱ�����߳���ֹrun()ѭ���¼�
        quit();
        wait();
    }

protected:
    void run()
    {
        qDebug() << "Woker run thread: " << QThread::currentThreadId();

        int nValue = 0;
        while(nValue < 100)
        {
            //����50ms
            msleep(50);
            ++nValue;

            //׼������
            emit resultReady(nValue);
        }


    }

signals:
    void resultReady(int value);
};

#endif // WORKTHREAD_H
