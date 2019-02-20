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
    std::condition_variable m_Queue_Not_Empty; //�ź�
    std::mutex m_Queue_Mutex; //������
    QQueue<QString> m_queue; //����
    int m_nQueue_Max_Size; //������󳤶�

public:
    Repository();

    //������
    void AddData(QString str);

    //ȡ����
    QString GetData();


};

#endif // PRODUCE_H
