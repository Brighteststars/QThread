#include "widget.h"
#include <QPushButton>
#include <QProgressBar>
#include <QVBoxLayout>

#include "workthread.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "Main Thread: " << QThread::currentThreadId();

    // ������ʼ��ť��������
    QPushButton *pStartButton = new QPushButton(this);
    m_pProgressBar = new QProgressBar(this);

    //�����ı���������ȡֵ��Χ
    pStartButton->setText(QString::fromLocal8Bit("��ʼ"));
    m_pProgressBar->setFixedHeight(25);
    m_pProgressBar->setRange(0, 100);
    m_pProgressBar->setValue(0);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pStartButton, 0, Qt::AlignHCenter);
    pLayout->addWidget(m_pProgressBar);
    pLayout->setSpacing(50);
    pLayout->setContentsMargins(10, 10, 10, 10);
    setLayout(pLayout);

    //�������߳�
    m_workThread = new WorkThread(this);

    //�ź����
    connect(pStartButton,SIGNAL(clicked(bool)),this,SLOT(startThread()));
    connect(m_workThread,SIGNAL(resultReady(int)),this,SLOT(handleResults(int)));
    //�߳̽�����,�Զ�����
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
