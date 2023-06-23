#include "timeset.h"
#include <QDebug>
timeSet::timeSet(QObject *parent) : QObject(parent)
{

}

void timeSet::setNTPServer(QString NTPServer)
{
    qDebug() << NTPServer;
    ntpIP = NTPServer;    //windows NTP服务器地址
}

void timeSet::setNtp()
{
    //ntpIP = "time.windows.com";    //windows NTP服务器地址

    m_udpSocket = new QUdpSocket(this);
    connect(m_udpSocket,SIGNAL(connected()),this,SLOT(connectsucess()));
    connect(m_udpSocket,SIGNAL(readyRead()),this,SLOT(readingDataGrams()));
    m_udpSocket->connectToHost(ntpIP,123);

}

void timeSet::connectsucess(){
       qint8 LI=0;  //无预告
       qint8 VN=3;  //版本号
       qint8 MODE=3; //客户端几
       qint8 STRATUM=0;//表示本地时钟层次水平
       qint8 POLL=4; //测试间隔
       qint8 PREC=-6; //表示本地时钟精度
       QDateTime Epoch(QDate(1900, 1, 1));
       qint32 second=quint32(Epoch.secsTo(QDateTime::currentDateTime()));

       qint32 temp=0;
       QByteArray timeRequest(48, 0);
       timeRequest[0]=(LI <<6) | (VN <<3) | (MODE);
       timeRequest[1]=STRATUM;
       timeRequest[2]=POLL;
       timeRequest[3]=PREC & 0xff;
       timeRequest[5]=1;
       timeRequest[9]=1;

       //40到43字节保存原始时间戳，即客户端发送的时间
       timeRequest[40]=(temp=(second&0xff000000)>>24);
       temp=0;
       timeRequest[41]=(temp=(second&0x00ff0000)>>16);
       temp=0;
       timeRequest[42]=(temp=(second&0x0000ff00)>>8);
       temp=0;
       timeRequest[43]=((second&0x000000ff));
       m_udpSocket -> flush();
       m_udpSocket -> write(timeRequest);
       m_udpSocket -> flush();
}

void timeSet::readingDataGrams()
{
    QByteArray newTime;
    QDateTime Epoch(QDate(1900, 1, 1));
    QDateTime unixStart(QDate(1970, 1, 1));
    do
    {
        newTime.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->read(newTime.data(), newTime.size());
    }while(m_udpSocket->hasPendingDatagrams());

    QByteArray TransmitTimeStamp ;
    TransmitTimeStamp=newTime.right(8);
    quint32 seconds=TransmitTimeStamp[0];
    quint8 temp=0;
    for(int j=1;j<=3;j++)
    {
        seconds=seconds<<8;
        temp=TransmitTimeStamp[j];
        seconds=seconds+temp;
    }

    m_NTPtime.setTime_t(seconds-Epoch.secsTo(unixStart));

    this->m_udpSocket->disconnectFromHost();
    this->m_udpSocket->close();
    qDebug() << m_NTPtime;
}

