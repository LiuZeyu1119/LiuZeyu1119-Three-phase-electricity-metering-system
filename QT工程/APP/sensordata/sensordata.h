 #ifndef SENSORDATA_H
#define SENSORDATA_H
#include <QTime>
#include <QTimer>
#include <QProcess>
#include <QUdpSocket>
#include <QDebug>
#include <QTextCodec>
#include <QString>
#include <QObject>
#include "LinkSDK/mqtt.h"
#include <QThread>
#include "sqlite/sqlite.h"
extern "C"{
#include "mqtt.h"
#include "mqtt4g.h"
#include <unistd.h>
#include <pthread.h>
}
class sensordata : public QObject
{
    Q_OBJECT
public:
    explicit            sensordata(QObject *parent = nullptr);
    virtual             ~sensordata();
    void                sensorInit();
    //Q_INVOKABLE QString             dataToQML(int number);
    int                 detcFreq = 1000;

    /****mqtt define****/

    int32_t     res = STATE_SUCCESS;
    void       *mqtt_handle = NULL;
    int8_t      public_instance = 1;  /* 用公共实例, 该参数要设置为1. 若用独享实例, 要将该参数设置为0 */
    char       *url = "a1hgnkSPPAP.iot-as-mqtt.cn-shanghai.aliyuncs.com"; /* 阿里云平台上海站点的域名后缀. TODO: 如果是企业实例, 要改成企业实例的接入点 */
    char        host[100] = {0}; /* 用这个数组拼接设备连接的云平台站点全地址, 规则是 ${productKey}.iot-as-mqtt.cn-shanghai.aliyuncs.com */
    uint16_t    port = 443;      /* 无论设备是否使用TLS连接阿里云平台, 目的端口都是443 */
    aiot_sysdep_network_cred_t cred; /* 安全凭据结构体, 如果要用TLS, 这个结构体中配置CA证书等参数 */
    int mqttSuccessFlag = 0;
    /* TODO: 替换为自己设备的三元组 */
    char *product_key       = "a1hgnkSPPAP";
    char *device_name       = "ATT7022";
    char *device_secret     = "c4565223ea4512247a574f64be328c1a";

    /******end define*/

    QString readFile(QString filePath);
    sensor_data m_data = {-1};
    Q_INVOKABLE sqlite m_sqlite;
    QSqlDatabase m_db;
    void detcSave();
    int detcToCloud(char* payload);
    int mqttDelete();
    //float powerConvert();
    char* dataPackage(sensor_data data);
signals:
    void    connectFailed();

public slots:
    int     mqttInit(); //initmqtt
    void detcMeter();

private:

    QTimer      *m_detcTimer;
};

class detcMoveToThread:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_data MEMBER m_data)
public:
    detcMoveToThread(QObject* parent=nullptr);
     ~detcMoveToThread();
    Q_INVOKABLE void                timeOver(); //qml time over
    Q_INVOKABLE QString             dataToQML(int index);
    Q_INVOKABLE void                dataToSQL();
signals:
    void dataChangedSIGN();
    void dataSave();
public slots:

private:
    QThread m_thread;  //定义的线程
   // QThread m_thread2;  //定义的线程2
    sensordata m_sensordata;  //定义的类
    //sensor_data m_data = {-1};
    QString m_data;  //保存接收数据
};

#endif // SENSORDATA_H
