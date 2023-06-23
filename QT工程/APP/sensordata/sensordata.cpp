#include "sensordata.h"
#include "LinkSDK/mqtt.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <qtextstream.h>
#include <QThread>

sensordata::sensordata(QObject *parent):QObject(parent)
{

}

void sensordata::sensorInit()
{
}

QString sensordata::readFile(QString filePath)
{
    
    QFile *file = new QFile;
    file->setFileName(filePath);
    bool ok = file->open(QIODevice::ReadOnly);

    if(ok)
    {
        QTextStream in(file);
        QString str = in.readAll();
        file->close();
        delete file;
        return str;
    }else{
        return "NULL";
    }
    return "NULL";
    /*QByteArray ba = filePath.toLatin1(); // must
    char* filename = ba.data();
    int err = 0;
    int fd;
    char buf[10];

    fd = open(filename,O_RDONLY);
    if(fd < 0) {
        ::close(fd);
        return "open file error!";
    }

    err = read(fd, buf, sizeof(buf));
    if (err < 0) {
        ::close(fd);
        return "read data error!";
    }

    ::close(fd);

    QString Value = buf;
    QStringList list = Value.split("\n");
    return list[0];*/
}
float powerConvert(float data){
    if(data > 8388605){
        return data = data - 16777216;
    }else{
        return data;
    }

}
float angleCovert(float data){
    if(data > 1048576){
        return data = data - 16777216;
    }else{
        return 0;
    }

}
void sensordata::detcMeter()
{
    qDebug() << "detcing";
    /*电压有效值*/
    m_data.r_UaRms = (readFile("/sys/bus/iio/devices/iio:device0/uarms").toFloat()/8192)*3.5;
    m_data.r_UbRms = (readFile("/sys/bus/iio/devices/iio:device0/ubrms").toFloat()/8192)*3.5;
    m_data.r_UcRms = (readFile("/sys/bus/iio/devices/iio:device0/ucrms").toFloat()/8192)*3.5;
    /*电压夹角*/
    m_data.uAB_angle = angleCovert(readFile("/sys/bus/iio/devices/iio:device0/yuaub").toFloat()/1048576)*180;
    m_data.uAC_angle = angleCovert(readFile("/sys/bus/iio/devices/iio:device0/yuaub").toFloat()/1048576)*180;
    m_data.uBC_angle = angleCovert(readFile("/sys/bus/iio/devices/iio:device0/yuaub").toFloat()/1048576)*180;
    /*流压夹角*/
    m_data.uiA_angle = angleCovert(readFile("/sys/bus/iio/devices/iio:device0/pga").toFloat()/1048576)*180;
    m_data.uiB_angle = angleCovert(readFile("/sys/bus/iio/devices/iio:device0/pgb").toFloat()/1048576)*180;
    m_data.uiC_angle = angleCovert(readFile("/sys/bus/iio/devices/iio:device0/pgc").toFloat()/1048576)*180;
    /*电流有效值*/
    m_data.r_IaRms = readFile("/sys/bus/iio/devices/iio:device0/iarms").toFloat()/8192/10;
    m_data.r_IbRms = readFile("/sys/bus/iio/devices/iio:device0/ibrms").toFloat()/8192/10;
    m_data.r_IcRms = readFile("/sys/bus/iio/devices/iio:device0/icrms").toFloat()/8192/10;
    m_data.r_ItRms = readFile("/sys/bus/iio/devices/iio:device0/itrms").toFloat()/8192/10;

    //频率
    m_data.Freq = readFile("/sys/bus/iio/devices/iio:device0/freq").toFloat()/8192;

    /*有功功率*/
    m_data.pN_a = -powerConvert(readFile("/sys/bus/iio/devices/iio:device0/pa").toFloat())/32;
    m_data.pN_b = -powerConvert(readFile("/sys/bus/iio/devices/iio:device0/pb").toFloat())/32;
    m_data.pN_c = -powerConvert(readFile("/sys/bus/iio/devices/iio:device0/pc").toFloat())/32;
    m_data.pN_t = -powerConvert(readFile("/sys/bus/iio/devices/iio:device0/pt").toFloat())/32;

    m_data.utrm = readFile("/sys/bus/iio/devices/iio:device0/utrm").toFloat();//电压和有效值
    m_data.itrm = readFile("/sys/bus/iio/devices/iio:device0/itrm").toFloat();//电压和有效值

    /*基波功率*/
    m_data.linepN_a = readFile("/sys/bus/iio/devices/iio:device0/linepa").toFloat();
    m_data.linepN_b = readFile("/sys/bus/iio/devices/iio:device0/linepb").toFloat();
    m_data.linepN_c = readFile("/sys/bus/iio/devices/iio:device0/linepc").toFloat();
    m_data.linepN_t = readFile("/sys/bus/iio/devices/iio:device0/linept").toFloat();
    
    m_data.lineEpN_a = readFile("/sys/bus/iio/devices/iio:device0/lineepa").toFloat();
    m_data.lineEpN_b = readFile("/sys/bus/iio/devices/iio:device0/lineepb").toFloat();
    m_data.lineEpN_c = readFile("/sys/bus/iio/devices/iio:device0/lineepc").toFloat();
    m_data.lineEpN_t = readFile("/sys/bus/iio/devices/iio:device0/lineept").toFloat();
    
    /*无功功率*/
    m_data.qN_a =  -powerConvert(readFile("/sys/bus/iio/devices/iio:device0/qa").toFloat())/32;
    m_data.qN_b =  -powerConvert(readFile("/sys/bus/iio/devices/iio:device0/qb").toFloat())/32;
    m_data.qN_c =  -powerConvert(readFile("/sys/bus/iio/devices/iio:device0/qc").toFloat())/32;
    m_data.qN_t =  -powerConvert(readFile("/sys/bus/iio/devices/iio:device0/qt").toFloat())/32;

    /*视在功率*/
    m_data.sN_a = readFile("/sys/bus/iio/devices/iio:device0/sa").toFloat()/32;
    m_data.sN_b = readFile("/sys/bus/iio/devices/iio:device0/sb").toFloat()/32;
    m_data.sN_c = readFile("/sys/bus/iio/devices/iio:device0/sc").toFloat()/32;
    m_data.sN_t = readFile("/sys/bus/iio/devices/iio:device0/st").toFloat()/32;

    /*功率因数*/
    m_data.epN_a = readFile("/sys/bus/iio/devices/iio:device0/pfa").toFloat()/8388608;
    m_data.epN_b = readFile("/sys/bus/iio/devices/iio:device0/pfb").toFloat()/8388608;
    m_data.epN_c = readFile("/sys/bus/iio/devices/iio:device0/pfc").toFloat()/8388608;
    m_data.epN_t = readFile("/sys/bus/iio/devices/iio:device0/pft").toFloat()/8388608;


    /*有功电能*/
    m_data.pFN_a = readFile("/sys/bus/iio/devices/iio:device0/epa").toFloat();
    m_data.pFN_b = readFile("/sys/bus/iio/devices/iio:device0/epb").toFloat();
    m_data.pFN_c = readFile("/sys/bus/iio/devices/iio:device0/epc").toFloat();
    m_data.pFN_t = readFile("/sys/bus/iio/devices/iio:device0/ept").toFloat();

    /*视在电能*/
    m_data.esN_a = readFile("/sys/bus/iio/devices/iio:device0/esa").toFloat();
    m_data.esN_b = readFile("/sys/bus/iio/devices/iio:device0/esb").toFloat();
    m_data.esN_c = readFile("/sys/bus/iio/devices/iio:device0/esc").toFloat();
    m_data.esN_t = readFile("/sys/bus/iio/devices/iio:device0/est").toFloat();

    /*芯片温度*/
    m_data.tpsd = 28.33;//readFile("/sys/bus/iio/devices/iio:device0/tpsd0").toFloat();
    char * payload = dataPackage(m_data);
    if(mqttSuccessFlag == 1)detcToCloud(payload);
}

void sensordata::detcSave(){
    qDebug() << "detcSaving!!!!";
    QString tableName =  m_sqlite.creatNewTable();
    QSqlQuery query;

    query = QSqlQuery(m_sqlite.db);
    QString queryStr = QString("INSERT INTO "+ tableName +"("
                                                  +"r_UaRms,"
                                                  +"r_UbRms, "
                                                  +"r_UcRms, "
                                                  +"uAB_angle, "
                                                  +"uAC_angle, "
                                                  +"uBC_angle, "
                                                  +"uiA_angle, "
                                                  +"uiB_angle, "
                                                  +"uiC_angle, "
                                                  +"r_IaRms, "
                                                  +"r_IbRms, "
                                                  +"r_IcRms, "
                                                  +"r_ItRms, "
                                                  +"Freq, "
                                                  +"pN_a, "
                                                  +"pN_b, "
                                                  +"pN_c, "
                                                  +"pN_t, "
                                                  +"utrm, "
                                                  +"itrm, "
                                                  +"linepN_a, "
                                                  +"linepN_b, "
                                                  +"linepN_c, "
                                                  +"linepN_t, "
                                                  +"lineEpN_a, "
                                                  +"lineEpN_b, "
                                                  +"lineEpN_c, "
                                                  +"lineEpN_t, "
                                                  +"qN_a, "
                                                  +"qN_b, "
                                                  +"qN_c, "
                                                  +"qN_t, "
                                                  +"sN_a, "
                                                  +"sN_b, "
                                                  +"sN_c, "
                                                  +"sN_t, "
                                                  +"epN_a, "
                                                  +"epN_b, "
                                                  +"epN_c, "
                                                  +"epN_t, "
                                                  +"pFN_a, "
                                                  +"pFN_b, "
                                                  +"pFN_c, "
                                                  +"pFN_t, "
                                                  +"esN_a, "
                                                  +"esN_b, "
                                                  +"esN_c, "
                                                  +"esN_t, "
                                                  +"tpsd"
                                                  +")VALUES('%1'"
                                                  +",'%2'"
                                                  +",'%3'"
                                                  +",'%4'"
                                                  +",'%5'"
                                                  +",'%6'"
                                                  +",'%7'"
                                                  +",'%8'"
                                                  +",'%9'"
                                                  +",'%10'"
                                                  +",'%11'"
                                                  +",'%12'"
                                                  +",'%13'"
                                                  +",'%14'"
                                                  +",'%15'"
                                                  +",'%16'"
                                                  +",'%17'"
                                                  +",'%18'"
                                                  +",'%19'"
                                                  +",'%20'"
                                                  +",'%21'"
                                                  +",'%22'"
                                                  +",'%23'"
                                                  +",'%24'"
                                                  +",'%25'"
                                                  +",'%26'"
                                                  +",'%27'"
                                                  +",'%28'"
                                                  +",'%29'"
                                                  +",'%30'"
                                                  +",'%31'"
                                                  +",'%32'"
                                                  +",'%33'"
                                                  +",'%34'"
                                                  +",'%35'"
                                                  +",'%36'"
                                                  +",'%37'"
                                                  +",'%38'"
                                                  +",'%39'"
                                                  +",'%40'"
                                                  +",'%41'"
                                                  +",'%42'"
                                                  +",'%43'"
                                                  +",'%44'"
                                                  +",'%45'"
                                                  +",'%46'"
                                                  +",'%47'"
                                                  +",'%48'"
                                                  +",'%49'"
                                                  +")")
                                                   .arg(m_data.r_UaRms)
                                                   .arg(m_data.r_UbRms)
                                                   .arg(m_data.r_UcRms)
                                                   .arg(m_data.uAB_angle)
                                                   .arg(m_data.uAC_angle)
                                                   .arg(m_data.uBC_angle)
                                                   .arg(m_data.uiA_angle)
                                                   .arg(m_data.uiB_angle)
                                                   .arg(m_data.uiC_angle)
                                                   .arg(m_data.r_IaRms)
                                                   .arg(m_data.r_IbRms)
                                                   .arg(m_data.r_IcRms)
                                                   .arg(m_data.r_ItRms)
                                                   .arg(m_data.Freq)
                                                   .arg(m_data.pN_a)
                                                   .arg(m_data.pN_b)
                                                   .arg(m_data.pN_c)
                                                   .arg(m_data.pN_t)
                                                   .arg(m_data.utrm)
                                                   .arg(m_data.itrm)
                                                   .arg(m_data.linepN_a)
                                                   .arg(m_data.linepN_b)
                                                   .arg(m_data.linepN_c)
                                                   .arg(m_data.linepN_t)
                                                   .arg(m_data.lineEpN_a)
                                                   .arg(m_data.lineEpN_b)
                                                   .arg(m_data.lineEpN_c)
                                                   .arg(m_data.lineEpN_t)
                                                   .arg(m_data.qN_a)
                                                   .arg(m_data.qN_b)
                                                   .arg(m_data.qN_c)
                                                   .arg(m_data.qN_t)
                                                   .arg(m_data.sN_a)
                                                   .arg(m_data.sN_b)
                                                   .arg(m_data.sN_c)
                                                   .arg(m_data.sN_t)
                                                   .arg(m_data.epN_a)
                                                   .arg(m_data.epN_b)
                                                   .arg(m_data.epN_c)
                                                   .arg(m_data.epN_t)
                                                   .arg(m_data.pFN_a)
                                                   .arg(m_data.pFN_b)
                                                   .arg(m_data.pFN_c)
                                                   .arg(m_data.pFN_t)
                                                   .arg(m_data.esN_a)
                                                   .arg(m_data.esN_b)
                                                   .arg(m_data.esN_c)
                                                   .arg(m_data.esN_t)
                                                   .arg(m_data.tpsd);
    qDebug() << queryStr;

    if(!query.exec(queryStr))
    {
        qDebug()<<"Error:Failed to add data"<<query.lastError();
    }
    else{
        qDebug()<<"Add data!";
    }

}

int sensordata::detcToCloud(char* payload){
    char *pub_topic = "/sys/a1hgnkSPPAP/ATT7022/thing/event/property/post";
    char *pub_payload = payload;
    qDebug()<<pub_payload;

    res = aiot_mqtt_pub(mqtt_handle, pub_topic, (uint8_t *)pub_payload, (uint32_t)strlen(pub_payload), 0);
    if (res < 0) {
    printf("aiot_mqtt_sub failed, res: -0x%04X\n", -res);
        //emit connectFailed();
        return -1;
    }
    return 0;
}

int sensordata::mqttDelete(){
    /* 断开MQTT连接, 一般不会运行到这里 */
       g_mqtt_process_thread_running = 0;
       g_mqtt_recv_thread_running = 0;
       sleep(1);
       res = aiot_mqtt_disconnect(mqtt_handle);
       if (res < STATE_SUCCESS) {
           aiot_mqtt_deinit(&mqtt_handle);
           printf("aiot_mqtt_disconnect failed: -0x%04X\n", -res);
           return -1;
       }

       /* 销毁MQTT实例, 一般不会运行到这里 */
       res = aiot_mqtt_deinit(&mqtt_handle);
       if (res < STATE_SUCCESS) {
           printf("aiot_mqtt_deinit failed: -0x%04X\n", -res);
           return -1;
       }

       pthread_join(g_mqtt_process_thread, NULL);
       pthread_join(g_mqtt_recv_thread, NULL);
       return 0;
}

char *sensordata::dataPackage(sensor_data packData)
{
    cJSON* cjson_root = NULL;
    cJSON* cjson_params = NULL;
    cJSON* cjson_sys = NULL;
    cJSON* cjson_nUa = NULL;
    cJSON* cjson_nUb = NULL;
    cJSON* cjson_nUc = NULL;
    cJSON* cjson_nIa = NULL;
    cJSON* cjson_nIb = NULL;
    cJSON* cjson_nIc = NULL;
    cJSON* cjson_electric_fr = NULL;
    cJSON* cjson_uAB_angle = NULL;
    cJSON* cjson_uBC_angle = NULL;
    cJSON* cjson_uAC_angle = NULL;
    cJSON* cjson_uiC_angle = NULL;
    cJSON* cjson_uiB_angle = NULL;
    cJSON* cjson_uiA_angle = NULL;
    cJSON* cjson_electric_fra = NULL;
    cJSON* cjson_electric_frb = NULL;
    cJSON* cjson_electric_frc = NULL;
    cJSON* cjson_electric_pqa = NULL;
    cJSON* cjson_electric_pqb = NULL;
    cJSON* cjson_electric_pqc = NULL;
    cJSON* cjson_electric_psa = NULL;
    cJSON* cjson_electric_psb = NULL;
    cJSON* cjson_electric_psc = NULL;
    cJSON* cjson_electric_pfa = NULL;
    cJSON* cjson_electric_pfb = NULL;
    cJSON* cjson_electric_pfc = NULL;
    cJSON* cjson_nActiveEnergy = NULL;

    /*create json node*/
    cjson_root = cJSON_CreateObject();
    cjson_params = cJSON_CreateObject();
    cjson_sys = cJSON_CreateObject();
    cjson_nUa = cJSON_CreateObject();
    cjson_nUb = cJSON_CreateObject();
    cjson_nUc = cJSON_CreateObject();
    cjson_nIa = cJSON_CreateObject();
    cjson_nIb = cJSON_CreateObject();
    cjson_nIc = cJSON_CreateObject();
    cjson_electric_fr = cJSON_CreateObject();
    cjson_uAB_angle = cJSON_CreateObject();
    cjson_uBC_angle = cJSON_CreateObject();
    cjson_uAC_angle = cJSON_CreateObject();
    cjson_uiA_angle = cJSON_CreateObject();
    cjson_uiB_angle = cJSON_CreateObject();
    cjson_uiC_angle = cJSON_CreateObject();
    cjson_electric_fra = cJSON_CreateObject();
    cjson_electric_frb = cJSON_CreateObject();
    cjson_electric_frc = cJSON_CreateObject();
    cjson_electric_pqa = cJSON_CreateObject();
    cjson_electric_pqb = cJSON_CreateObject();
    cjson_electric_pqc = cJSON_CreateObject();
    cjson_electric_psa = cJSON_CreateObject();
    cjson_electric_psb = cJSON_CreateObject();
    cjson_electric_psc = cJSON_CreateObject();
    cjson_electric_pfa = cJSON_CreateObject();
    cjson_electric_pfb = cJSON_CreateObject();
    cjson_electric_pfc = cJSON_CreateObject();
    cjson_nActiveEnergy = cJSON_CreateObject();
    QDateTime dateTime = QDateTime::currentDateTime();
    long long timeStamp = dateTime.toMSecsSinceEpoch();
    qDebug() << timeStamp;
    /*add string to json node*/
    cJSON_AddStringToObject(cjson_root, "id", "123");
    cJSON_AddStringToObject(cjson_root, "version", "1.0");

    /*add int to json node*/
    cJSON_AddNumberToObject(cjson_sys, "ack", 0);

    /*add node to node*/
    cJSON_AddItemToObject(cjson_root, "sys", cjson_sys);

    /*add float to json node*/
    cJSON_AddNumberToObject(cjson_nUa, "value", packData.r_UaRms);
    cJSON_AddNumberToObject(cjson_nUa, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_nUb, "value", packData.r_UbRms);
    cJSON_AddNumberToObject(cjson_nUb, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_nUc, "value", packData.r_UcRms);
    cJSON_AddNumberToObject(cjson_nUc, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_nIa, "value", packData.r_IaRms);
    cJSON_AddNumberToObject(cjson_nIa, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_nIb, "value", packData.r_IbRms);
    cJSON_AddNumberToObject(cjson_nIb, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_nIc, "value", packData.r_IcRms);
    cJSON_AddNumberToObject(cjson_nIc, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_electric_fr, "value", packData.Freq);
    cJSON_AddNumberToObject(cjson_electric_fr, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_uAB_angle, "value", packData.uAB_angle);
    cJSON_AddNumberToObject(cjson_uAB_angle, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_uBC_angle, "value", packData.uBC_angle);
    cJSON_AddNumberToObject(cjson_uBC_angle, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_uAC_angle, "value", packData.uAC_angle);
    cJSON_AddNumberToObject(cjson_uAC_angle, "time", timeStamp);


    cJSON_AddNumberToObject(cjson_uiA_angle, "value", packData.uiA_angle);
    cJSON_AddNumberToObject(cjson_uiA_angle, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_uiB_angle, "value", packData.uiB_angle);
    cJSON_AddNumberToObject(cjson_uiB_angle, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_uiC_angle, "value", packData.uiC_angle);
    cJSON_AddNumberToObject(cjson_uiC_angle, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_electric_fra, "value", packData.pN_a);
    cJSON_AddNumberToObject(cjson_electric_fra, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_electric_frb, "value", packData.pN_b);
    cJSON_AddNumberToObject(cjson_electric_frb, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_electric_frc, "value", packData.pN_c);
    cJSON_AddNumberToObject(cjson_electric_frc, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_electric_pqa, "value", packData.qN_a);
    cJSON_AddNumberToObject(cjson_electric_pqa, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_electric_pqb, "value", packData.qN_b);
    cJSON_AddNumberToObject(cjson_electric_pqb, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_electric_pqc, "value", packData.qN_c);
    cJSON_AddNumberToObject(cjson_electric_pqc, "time", timeStamp);


    cJSON_AddNumberToObject(cjson_electric_psa, "value", packData.sN_a);
    cJSON_AddNumberToObject(cjson_electric_psa, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_electric_psb, "value", packData.sN_b);
    cJSON_AddNumberToObject(cjson_electric_psb, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_electric_psc, "value", packData.sN_c);
    cJSON_AddNumberToObject(cjson_electric_psc, "time", timeStamp);


    cJSON_AddNumberToObject(cjson_electric_pfa, "value", packData.pFN_a);
    cJSON_AddNumberToObject(cjson_electric_pfa, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_electric_pfb, "value", packData.pFN_b);
    cJSON_AddNumberToObject(cjson_electric_pfb, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_electric_pfc, "value", packData.pFN_c);
    cJSON_AddNumberToObject(cjson_electric_pfc, "time", timeStamp);

    cJSON_AddNumberToObject(cjson_nActiveEnergy, "value", packData.epN_t);
    cJSON_AddNumberToObject(cjson_nActiveEnergy, "time", timeStamp);
    //,,,

    /*add node to node*/
    cJSON_AddItemToObject(cjson_params, "nUa", cjson_nUa);
    cJSON_AddItemToObject(cjson_params, "nUb", cjson_nUb);
    cJSON_AddItemToObject(cjson_params, "nUc", cjson_nUc);
    cJSON_AddItemToObject(cjson_params, "nIa", cjson_nIa);
    cJSON_AddItemToObject(cjson_params, "nIb", cjson_nIb);
    cJSON_AddItemToObject(cjson_params, "nIc", cjson_nIc);
    cJSON_AddItemToObject(cjson_params, "electric_fr", cjson_electric_fr);
    cJSON_AddItemToObject(cjson_params, "uAB_angles", cjson_uAB_angle);
    cJSON_AddItemToObject(cjson_params, "uBC_angles", cjson_uBC_angle);
    cJSON_AddItemToObject(cjson_params, "uAC_angles", cjson_uAC_angle);
    cJSON_AddItemToObject(cjson_params, "uiA_angle", cjson_uiA_angle);
    cJSON_AddItemToObject(cjson_params, "uiB_angle", cjson_uiB_angle);
    cJSON_AddItemToObject(cjson_params, "uiC_angle", cjson_uiC_angle);
    cJSON_AddItemToObject(cjson_params, "electric_fra", cjson_electric_fra);
    cJSON_AddItemToObject(cjson_params, "electric_frb", cjson_electric_frb);
    cJSON_AddItemToObject(cjson_params, "electric_frc", cjson_electric_frc);
    cJSON_AddItemToObject(cjson_params, "electric_pqa", cjson_electric_pqa);
    cJSON_AddItemToObject(cjson_params, "electric_pqb", cjson_electric_pqb);
    cJSON_AddItemToObject(cjson_params, "electric_pqc", cjson_electric_pqc);
    cJSON_AddItemToObject(cjson_params, "electric_psa", cjson_electric_psa);
    cJSON_AddItemToObject(cjson_params, "electric_psb", cjson_electric_psb);
    cJSON_AddItemToObject(cjson_params, "electric_psc", cjson_electric_psc);
    cJSON_AddItemToObject(cjson_params, "electric_pfa", cjson_electric_pfa);
    cJSON_AddItemToObject(cjson_params, "electric_pfb", cjson_electric_pfb);
    cJSON_AddItemToObject(cjson_params, "electric_pfc", cjson_electric_pfc);
    cJSON_AddItemToObject(cjson_params, "nActiveEnergy", cjson_nActiveEnergy);

    /*add node to node*/
    cJSON_AddItemToObject(cjson_root, "params", cjson_params);

    /*add string to json node*/
    cJSON_AddStringToObject(cjson_root, "method", "thing.event.property.post");
    char * str = cJSON_Print(cjson_root);
    printf("%s\n", str);
    cJSON_Delete(cjson_root);
    return str;
}

int sensordata::mqttInit(){
    /* AT模组硬件初始化 */

    at_hal_init();
    /* 配置SDK的底层依赖 */
    aiot_sysdep_set_portfile(&g_aiot_sysdep_portfile);
    /* 配置SDK的日志输出 */
    aiot_state_set_logcb(demo_state_logcb);
    /* 创建SDK的安全凭据, 用于建立TLS连接 */
    memset(&cred, 0, sizeof(aiot_sysdep_network_cred_t));
    cred.option = AIOT_SYSDEP_NETWORK_CRED_SVRCERT_CA;  /* 使用RSA证书校验MQTT服务端 */
    cred.max_tls_fragment = 16384; /* 最大的分片长度为16K, 其它可选值还有4K, 2K, 1K, 0.5K */
    cred.sni_enabled = 1;                               /* TLS建连时, 支持Server Name Indicator */
    cred.x509_server_cert = ali_ca_cert;                 /* 用来验证MQTT服务端的RSA根证书 */
    cred.x509_server_cert_len = strlen(ali_ca_cert);     /* 用来验证MQTT服务端的RSA根证书长度 */

    /* 创建1个MQTT客户端实例并内部初始化默认参数 */
    mqtt_handle = aiot_mqtt_init();
    if (mqtt_handle == NULL) {
        printf("aiot_mqtt_init failed\n");
        //emit connectFailed();
        return -1;

    }
    memset(&cred, 0, sizeof(aiot_sysdep_network_cred_t));
    cred.option = AIOT_SYSDEP_NETWORK_CRED_NONE;
    if (1 == public_instance) {
            snprintf(host, 100, "%s.%s", product_key, url);
        } else {
            snprintf(host, 100, "%s", url);
        }

        /* 配置MQTT服务器地址 */
        aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_HOST, (void *)host);
        /* 配置MQTT服务器端口 */
        aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PORT, (void *)&port);
        /* 配置设备productKey */
        aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PRODUCT_KEY, (void *)product_key);
        /* 配置设备deviceName */
        aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_NAME, (void *)device_name);
        /* 配置设备deviceSecret */
        aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_SECRET, (void *)device_secret);
        /* 配置网络连接的安全凭据, 上面已经创建好了 */
        aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_NETWORK_CRED, (void *)&cred);
        /* 配置MQTT默认消息接收回调函数 */
        aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_RECV_HANDLER, (void *)demo_mqtt_default_recv_handler);
        /* 配置MQTT事件回调函数 */
        aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_EVENT_HANDLER, (void *)demo_mqtt_event_handler);

        /* 与服务器建立MQTT连接 */
        res = aiot_mqtt_connect(mqtt_handle);
        if (res < STATE_SUCCESS) {
            /* 尝试建立连接失败, 销毁MQTT实例, 回收资源 */
            aiot_mqtt_deinit(&mqtt_handle);
            qDebug() << "qdebug : aiot_mqtt_connect failed: -0x\n" << QString::number(-res,16);
            printf("printf : aiot_mqtt_connect failed: -0x%04X\n", -res);
            //emit connectFailed();
            return -1;
        }

        /* MQTT 订阅topic功能*/
        //{
        char *sub_topic = "/sys/a1hgnkSPPAP/ATT7022/thing/event/property/post_reply";

        res = aiot_mqtt_sub(mqtt_handle, sub_topic, NULL, 1, NULL);
            if (res < 0) {
                printf("aiot_mqtt_sub failed, res: -0x%04X\n", -res);
                //emit connectFailed();
                return -1;
            }
       // }

        /* MQTT 发布消息功能 */
       /* {
       char *pub_topic = "/sys/a1hgnkSPPAP/ATT7022/thing/event/property/post";
       char *pub_payload = "{\"id\":\"1\",\"version\":\"1.0\",\"params\":{\"LightSwitch\":0}}";

            res = aiot_mqtt_pub(mqtt_handle, pub_topic, (uint8_t *)pub_payload, (uint32_t)strlen(pub_payload), 0);
            if (res < 0) {
                printf("aiot_mqtt_sub failed, res: -0x%04X\n", -res);
                //emit connectFailed();
                return -1;
            }
        }*/

        /* 创建一个单独的线程, 专用于执行aiot_mqtt_process, 它会自动发送心跳保活, 以及重发QoS1的未应答报文 */
        g_mqtt_process_thread_running = 1;
        res = pthread_create(&g_mqtt_process_thread, NULL, demo_mqtt_process_thread, mqtt_handle);
        qDebug() << "thread create!";
        if (res < 0) {
            printf("pthread_create demo_mqtt_process_thread failed: %d\n", res);
            //emit connectFailed();
            return -1;

        }

        /* 创建一个单独的线程用于执行aiot_mqtt_recv, 它会循环收取服务器下发的MQTT消息, 并在断线时自动重连 */
        g_mqtt_recv_thread_running = 1;
        res = pthread_create(&g_mqtt_recv_thread, NULL, demo_mqtt_recv_thread, mqtt_handle);
        if (res < 0) {
            printf("pthread_create demo_mqtt_recv_thread failed: %d\n", res);
            //emit connectFailed();
            return -1;
        }
        return 0;
}

sensordata::~sensordata(){
}

detcMoveToThread::detcMoveToThread(QObject *parent)
{
    system("insmod ATT7022EU.ko");
    system("insmod 8723ds.ko");
    system("insmod /home/root/ATT7022EU.ko");
    system("insmod /homr/root/8723ds.ko");
    m_sensordata.moveToThread(&m_thread); //加入到子线程  
    connect(this,&detcMoveToThread::dataChangedSIGN,&m_sensordata,&sensordata::detcMeter);
    connect(&m_sensordata,&sensordata::connectFailed,&m_sensordata,&sensordata::mqttInit);
    m_thread.start(); //开启子线程

    if(m_sensordata.mqttInit() != -1){
        qDebug() << "mqtt init success";
        m_sensordata.mqttSuccessFlag = 1;
    }else{
        qDebug() << "mqtt init failed";
        m_sensordata.mqttSuccessFlag = 0;
        emit m_sensordata.connectFailed();
    }

}

detcMoveToThread::~detcMoveToThread()
{
    m_sensordata.mqttDelete();
    m_thread.exit();
    m_thread.wait();

}

void detcMoveToThread::timeOver()
{
    //qDebug() << "timeover";
    emit dataChangedSIGN();
}

QString detcMoveToThread::dataToQML(int index)
{
    switch (index) {
        /*电压有效值*/
        case 0x01:
        return QString::number(m_sensordata.m_data.r_UaRms, 'f', 2);
        //return QString::number(m_sensordata.m_data.r_UaRms);
        case 0x02:
        return QString::number(m_sensordata.m_data.r_UbRms, 'f', 2);
        case 0x03:
        return QString::number(m_sensordata.m_data.r_UcRms, 'f', 2);
        /*电压夹角*/
        case 0x04:
        return QString::number(m_sensordata.m_data.uAB_angle, 'f', 2);
        case 0x05:
        return QString::number(m_sensordata.m_data.uAC_angle, 'f', 2);
        case 0x06:
        return QString::number(m_sensordata.m_data.uBC_angle, 'f', 2);
        /*流压夹角*/
        case 0x07:
        return QString::number(m_sensordata.m_data.uiA_angle, 'f', 2);
        case 0x08:
        return QString::number(m_sensordata.m_data.uiB_angle, 'f', 2);
        case 0x09:
        return QString::number(m_sensordata.m_data.uiC_angle, 'f', 2);
        /*电流有效值*/
        case 0x0a:
        return QString::number(m_sensordata.m_data.r_IaRms, 'f', 2);
        case 0x0b:
        return QString::number(m_sensordata.m_data.r_IbRms, 'f', 2);
        case 0x0c:
        return QString::number(m_sensordata.m_data.r_IcRms, 'f', 2);
        case 0x0d:
        return QString::number(m_sensordata.m_data.r_ItRms, 'f', 2);
        //频率
        case 0x0e:
        return QString::number(m_sensordata.m_data.Freq, 'f', 2);
        /*有功功率*/
        case 0x0f:
        return QString::number(m_sensordata.m_data.pN_a, 'f', 2);
        case 0x10:
        return QString::number(m_sensordata.m_data.pN_b, 'f', 2);
        case 0x11:
        return QString::number(m_sensordata.m_data.pN_c, 'f', 2);
        case 0x12:
        return QString::number(m_sensordata.m_data.pN_t, 'f', 2);
        /*矢量电压和有效值*/
        case 0x13:
        return QString::number(m_sensordata.m_data.utrm, 'f', 2);
        case 0x14:
        return QString::number(m_sensordata.m_data.itrm, 'f', 2);
        /*基波功率*/
        case 0x16:
        return QString::number(m_sensordata.m_data.linepN_a, 'f', 2);
        case 0x17:
        return QString::number(m_sensordata.m_data.linepN_b, 'f', 2);
        case 0x18:
        return QString::number(m_sensordata.m_data.linepN_c, 'f', 2);
        case 0x19:
        return QString::number(m_sensordata.m_data.linepN_t, 'f', 2);
        /*基波dianneng*/
        case 0x1a:
        return QString::number(m_sensordata.m_data.lineEpN_a, 'f', 2);
        case 0x1b:
        return QString::number(m_sensordata.m_data.lineEpN_b, 'f', 2);
        case 0x1c:
        return QString::number(m_sensordata.m_data.lineEpN_c, 'f', 2);
        case 0x1d:
        return QString::number(m_sensordata.m_data.lineEpN_t, 'f', 2);
        /*无功功率*/
        case 0x1e:
        return QString::number(m_sensordata.m_data.qN_a, 'f', 2);
        case 0x1f:
        return QString::number(m_sensordata.m_data.qN_b, 'f', 2);
        case 0x20:
        return QString::number(m_sensordata.m_data.qN_c, 'f', 2);
        case 0x21:
        return QString::number(m_sensordata.m_data.qN_t, 'f', 2);
        /*视在功率*/
        case 0x22:
        return QString::number(m_sensordata.m_data.sN_a, 'f', 2);
        case 0x23:
        return QString::number(m_sensordata.m_data.sN_b, 'f', 2);
        case 0x24:
        return QString::number(m_sensordata.m_data.sN_c, 'f', 2);
        case 0x25:
        return QString::number(m_sensordata.m_data.sN_t, 'f', 2);
        /*功率因数*/
        case 0x26:
        return QString::number(m_sensordata.m_data.pFN_a, 'f', 2);
        case 0x27:
        return QString::number(m_sensordata.m_data.pFN_b, 'f', 2);
        case 0x28:
        return QString::number(m_sensordata.m_data.pFN_c, 'f', 2);
        case 0x29:
        return QString::number(m_sensordata.m_data.pFN_t, 'f', 2);
        /*有功电能*/
        case 0x2a:
        return QString::number(m_sensordata.m_data.epN_a, 'f', 2);
        case 0x2b:
        return QString::number(m_sensordata.m_data.epN_b, 'f', 2);
        case 0x2c:
        return QString::number(m_sensordata.m_data.epN_c, 'f', 2);
        case 0x2d:
        return QString::number(m_sensordata.m_data.epN_t, 'f', 2);
        /*视在电能*/
        case 0x2f:
        return QString::number(m_sensordata.m_data.esN_a, 'f', 2);
        case 0x30:
        return QString::number(m_sensordata.m_data.esN_b, 'f', 2);
        case 0x31:
        return QString::number(m_sensordata.m_data.esN_c, 'f', 2);
        case 0x32:
        return QString::number(m_sensordata.m_data.esN_t, 'f', 2);
        /*芯片温度*/
        case 0x33:
        return QString::number(m_sensordata.m_data.tpsd, 'f', 2);

    default:
        return "null";
    }

}

void detcMoveToThread::dataToSQL(){
    m_sensordata.m_sqlite.connectSQL();
    m_sensordata.detcSave();
    m_sensordata.m_sqlite.closeSQL();
}

