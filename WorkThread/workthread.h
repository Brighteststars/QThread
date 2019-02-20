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
        //在主线程上构造了WorkThread
        qDebug() << "Worker Thread: " << QThread::currentThreadId();
    }

    ~WorkThread()
    {
        //防止主线程访问公共资源时,子线程调用run()在访问公共资源,请求中断子线程
//        requestInterruption();

        //主线程调用析构函数时,阻塞析构函数,直到子线程终止run()循环事件
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
            //休眠50ms
            msleep(50);
            ++nValue;

            //准备更新
            emit resultReady(nValue);
        }


    }

signals:
    void resultReady(int value);
};

#endif // WORKTHREAD_H
