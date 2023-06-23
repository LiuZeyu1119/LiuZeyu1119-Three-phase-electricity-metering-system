#ifndef TOPBAR_H
#define TOPBAR_H

#include <QTime>
#include <QTimer>
#include <QProcess>
#include <QUdpSocket>
#include <QDebug>
#include <QTextCodec>
#include <QString>
#include <QObject>
class topBar : public QObject
{
    Q_OBJECT
public:
    explicit topBar(QObject *parent = nullptr);

signals:

public slots:

private:

};

#endif // TOPBAR_H
