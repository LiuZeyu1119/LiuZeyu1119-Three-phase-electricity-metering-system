#ifndef TIMESET_H
#define TIMESET_H
#include <QUdpSocket>
#include <QObject>
#include <QDateTime>
class timeSet : public QObject
{
    Q_OBJECT
public:
    explicit timeSet(QObject *parent = nullptr);
    Q_INVOKABLE void setNTPServer(QString NTPServer);
signals:
    void connected();
    void readyRead();
public slots:
    void setNtp();
    void connectsucess();
    void readingDataGrams();
public:
    QString ntpIP = "time.windows.com";    //windows NTP服务器地址;
    QUdpSocket  *m_udpSocket;
    QDateTime    m_NTPtime;
};

#endif // TIMESET_H
