#ifndef PRODUCE_H
#define PRODUCE_H

#include <condition_variable>
#include <chrono>
#include <thread>
#include <QQueue>


class Repository
{
private:
    std::condition_variable m_Queue_Not_Full;
    std::condition_variable m_Queue_Not_Empty; //信号
    std::mutex m_Queue_Mutex; //队列锁
    QQueue<QString> m_queue; //队列
    int m_nQueue_Max_Size; //队列最大长度

public:
    Repository();

    //存数据
    void AddData(QString str);

    //取数据
    QString GetData();


};

#endif // PRODUCE_H
