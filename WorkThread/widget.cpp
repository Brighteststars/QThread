#include "widget.h"
#include <QPushButton>
#include <QProgressBar>
#include <QVBoxLayout>

#include "workthread.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "Main Thread: " << QThread::currentThreadId();

    // 创建开始按钮、进度条
    QPushButton *pStartButton = new QPushButton(this);
    m_pProgressBar = new QProgressBar(this);

    //设置文本、进度条取值范围
    pStartButton->setText(QString::fromLocal8Bit("开始"));
    m_pProgressBar->setFixedHeight(25);
    m_pProgressBar->setRange(0, 100);
    m_pProgressBar->setValue(0);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pStartButton, 0, Qt::AlignHCenter);
    pLayout->addWidget(m_pProgressBar);
    pLayout->setSpacing(50);
    pLayout->setContentsMargins(10, 10, 10, 10);
    setLayout(pLayout);

    //创建子线程
    m_workThread = new WorkThread(this);

    //信号与槽
    connect(pStartButton,SIGNAL(clicked(bool)),this,SLOT(startThread()));
    connect(m_workThread,SIGNAL(resultReady(int)),this,SLOT(handleResults(int)));
    //线程结束后,自动销毁
    connect(m_workThread,SIGNAL(finished()),m_workThread,SLOT(deleteLater()));
}

Widget::~Widget()
{

}

void Widget::handleResults(int value)
{
    qDebug() << "Handle Thread: " << QThread::currentThreadId();
    m_pProgressBar->setValue(value);

}

void Widget::startThread()
{
    if(!m_workThread->isRunning())
    {
        m_workThread->start();
    }
}
