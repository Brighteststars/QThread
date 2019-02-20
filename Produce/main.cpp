#include <QCoreApplication>
#include "produce.h"
int g_nProduceCount = 100;


//模拟写入100行数据
void ProduceTask(Repository* pR)
{
    for(int i = 0;i < g_nProduceCount;i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); //当前线程睡眠100ms
        QString str = QString("Produce %1").arg(i);
        pR->AddData(str);
    }
}

//模拟读取100行数据
void ConsumerTask(Repository* pR)
{
    for(int i = 0;i < g_nProduceCount;i++)
    {
        QString str = pR->GetData();
        //模拟文件读取,耗时200ms
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Repository re;
    std::thread Produce(ProduceTask,&re);
    std::thread Consumer(ConsumerTask,&re);

    Produce.join();
    Consumer.join();

    return a.exec();
}
