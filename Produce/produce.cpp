#include "produce.h"



Repository::Repository()
{
    m_nQueue_Max_Size = 10;
}

void Repository::AddData(QString str)
{
    std::unique_lock<std::mutex> lock(m_Queue_Mutex);
    //判断队列是否满
    if(m_queue.count() >= m_nQueue_Max_Size)
    {

        m_Queue_Not_Full.wait(lock);
    }

    m_queue.enqueue(str);

    m_Queue_Not_Empty.notify_all();


}

QString Repository::GetData()
{
    std::unique_lock<std::mutex> lock(m_Queue_Mutex);
    //判断队列是否为空
    if(m_queue.isEmpty())
    {
        m_Queue_Not_Empty.wait(lock);
    }

    QString str = m_queue.dequeue();

    m_Queue_Not_Full.notify_all();

    return str;
}


