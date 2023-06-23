#ifndef SQLITE_H
#define SQLITE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <LinkSDK/mqtt.h>
class sqlite : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList model MEMBER m_model NOTIFY modelChanged)
    Q_PROPERTY(QStringList dataModel MEMBER m_dataModel NOTIFY dataModelChanged)

public:
    explicit sqlite(QObject *parent = nullptr);
    QSqlDatabase db;
    sensor_data historydata;
    QSqlQuery query;
    void connectSQL();
    void searchSQL();
    void closeSQL();
    Q_INVOKABLE void refreshList();
    Q_INVOKABLE void refreshData(QString targetTable);
    Q_INVOKABLE QString dataToQML(int index);
    QString creatNewTable();
    QStringList m_model;
    QString m_dataModelStr;
    QStringList m_dataModel;

private:

public slots:
    void setModel(QString m) {
      m_model = m.split(" ");
      modelChanged();
    }
signals:
    void modelChanged();
    void dataModelChanged();


};


#endif // SQLITE_H
