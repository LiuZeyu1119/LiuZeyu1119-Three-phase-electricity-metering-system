#include "sqlite.h"
#include <QDebug>
#include <QDateTime>
sqlite::sqlite(QObject *parent) : QObject(parent)
{

}

void sqlite::connectSQL()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    if(db.open())
    {
        qDebug() << "open success!";

    }else{
        qDebug() << "open failed!";
    }
}

void sqlite::searchSQL()
{
    query.exec("SELECT * FROM sensordata;");
    while(query.next())
    {
        /*电压有效值*/
        historydata.r_UaRms = query.value(0).toFloat();
        historydata.r_UbRms = query.value(1).toFloat();
        historydata.r_UcRms = query.value(2).toFloat();
        /*电压夹角*/
        historydata.uAB_angle = query.value(3).toFloat();
        historydata.uAC_angle = query.value(4).toFloat();
        historydata.uBC_angle = query.value(5).toFloat();
        /*流压夹角*/
        historydata.uiA_angle = query.value(6).toFloat();
        historydata.uiB_angle = query.value(7).toFloat();
        historydata.uiC_angle = query.value(8).toFloat();
        /*电流有效值*/
        historydata.r_IaRms = query.value(9).toFloat();
        historydata.r_IbRms = query.value(10).toFloat();
        historydata.r_IcRms = query.value(11).toFloat();
        historydata.r_ItRms = query.value(12).toFloat();

        //频率
        historydata.Freq = query.value(13).toFloat();

        /*有功功率*/
        historydata.pN_a = query.value(14).toFloat();
        historydata.pN_b = query.value(15).toFloat();
        historydata.pN_c = query.value(16).toFloat();
        historydata.pN_t = query.value(17).toFloat();

        historydata.utrm = query.value(18).toFloat();//电压和有效值
        historydata.itrm = query.value(19).toFloat();//电压和有效值

        /*基波功率*/
        historydata.linepN_a = query.value(20).toFloat();
        historydata.linepN_b = query.value(21).toFloat();
        historydata.linepN_c = query.value(22).toFloat();
        historydata.linepN_t = query.value(23).toFloat();

        historydata.lineEpN_a = query.value(24).toFloat();
        historydata.lineEpN_b = query.value(25).toFloat();
        historydata.lineEpN_c = query.value(26).toFloat();
        historydata.lineEpN_t = query.value(27).toFloat();

        /*无功功率*/
        historydata.qN_a = query.value(28).toFloat();
        historydata.qN_b = query.value(29).toFloat();
        historydata.qN_c = query.value(30).toFloat();
        historydata.qN_t = query.value(31).toFloat();

        /*视在功率*/
        historydata.sN_a = query.value(32).toFloat();
        historydata.sN_b = query.value(33).toFloat();
        historydata.sN_c = query.value(34).toFloat();
        historydata.sN_t = query.value(35).toFloat();

        /*功率因数*/
        historydata.epN_a = query.value(36).toFloat();
        historydata.epN_b = query.value(37).toFloat();
        historydata.epN_c = query.value(38).toFloat();
        historydata.epN_t = query.value(39).toFloat();


        /*有功电能*/
        historydata.pFN_a = query.value(40).toFloat();
        historydata.pFN_b = query.value(41).toFloat();
        historydata.pFN_c = query.value(42).toFloat();
        historydata.pFN_t = query.value(43).toFloat();

        /*视在电能*/
        historydata.esN_a = query.value(44).toFloat();
        historydata.esN_b = query.value(45).toFloat();
        historydata.esN_c = query.value(46).toFloat();
        historydata.esN_t = query.value(47).toFloat();

        /*芯片温度*/
        historydata.esN_t = query.value(48).toFloat();
        //historydata.time = query.value(48).toQString();//QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    }
}

QString sqlite::creatNewTable()
{
    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    QString timeStr = dateTime.toString("yyyyMMddhhmmss");//格式化时间
    QString queryStr;
    QString tableName = "SensorData"+ timeStr;
    qDebug() << tableName;
    query = QSqlQuery(this->db);
    queryStr = "CREATE TABLE "+ tableName + "("
                       "r_UaRms REAL,"
                       "r_UbRms REAL, "
                       "r_UcRms REAL, "
                       "uAB_angle REAL, "
                       "uAC_angle REAL, "
                       "uBC_angle REAL, "
                       "uiA_angle REAL, "
                       "uiB_angle REAL, "
                       "uiC_angle REAL, "
                       "r_IaRms REAL, "
                       "r_IbRms REAL, "
                       "r_IcRms REAL, "
                       "r_ItRms REAL, "
                       "Freq REAL, "
                       "pN_a REAL, "
                       "pN_b REAL, "
                       "pN_c REAL, "
                       "pN_t REAL, "
                       "utrm REAL, "
                       "itrm REAL, "
                       "linepN_a REAL, "
                       "linepN_b REAL, "
                       "linepN_c REAL, "
                       "linepN_t REAL, "
                       "lineEpN_a REAL, "
                       "lineEpN_b REAL, "
                       "lineEpN_c REAL, "
                       "lineEpN_t REAL, "
                       "qN_a REAL, "
                       "qN_b REAL, "
                       "qN_c REAL, "
                       "qN_t REAL, "
                       "sN_a REAL, "
                       "sN_b REAL, "
                       "sN_c REAL, "
                       "sN_t REAL, "
                       "epN_a REAL, "
                       "epN_b REAL, "
                       "epN_c REAL, "
                       "epN_t REAL, "
                       "pFN_a REAL, "
                       "pFN_b REAL, "
                       "pFN_c REAL, "
                       "pFN_t REAL, "
                       "esN_a REAL, "
                       "esN_b REAL, "
                       "esN_c REAL, "
                       "esN_t REAL, "
                       "tpsd REAL) ";
    qDebug() << queryStr;
    if(!query.exec(queryStr))
    {
        qDebug()<<"Error:Failed to create table"<<query.lastError();
    }
    else{
        qDebug()<<"Table created!";
    }
    return tableName;
    //query.exec(queryStr);
}

void sqlite::closeSQL(){
    db.close();
}

void sqlite::refreshList(){

    connectSQL();
    QString queryStr;
    m_model.clear();
    query = QSqlQuery(this->db);
    queryStr = "SELECT name FROM sqlite_master WHERE type='table' order by name";
    qDebug() << queryStr;
    query.exec(queryStr);
    while (query.next()){
        int i = 0;
        QString result;
        QVariant temp;
        while ((temp = query.value(i++)).isValid()){
            result += temp.toString();
            //result += " | ";
            m_model<<result;
        }


    }
    qDebug() << m_model;

    emit modelChanged();
    closeSQL();
}

void sqlite::refreshData(QString targetTable){
    connectSQL();
    QString queryStr;
    float tmp;
    query = QSqlQuery(this->db);
    queryStr = "SELECT * FROM "+targetTable;
    qDebug() << queryStr;
    query.exec(queryStr);
    while (query.next()){
        int i = 0;
        QString result;
        QVariant temp;
        while ((temp = query.value(i++)).isValid()){
            tmp = temp.toFloat();
            result =QString::number(tmp, 'f', 2);// temp.toString();
            m_dataModel<<result;
        }
    }
    //qDebug() << m_dataModel[48];
    emit dataModelChanged();
    closeSQL();
}

QString sqlite::dataToQML(int index){
    switch (index) {
        /*电压有效值*/
        case 0x01:
        return QString("%2").arg(m_dataModel[0]);
        case 0x02:
        return QString("%2").arg(m_dataModel[1]);
        case 0x03:
        return QString("%2").arg(m_dataModel[2]);
        /*电压夹角*/
        case 0x04:
        return QString("%2").arg(m_dataModel[3]);
        case 0x05:
        return QString("%2").arg(m_dataModel[4]);
        case 0x06:
        return QString("%2").arg(m_dataModel[5]);
        /*流压夹角*/
        case 0x07:
        return QString("%2").arg(m_dataModel[6]);
        case 0x08:
        return QString("%2").arg(m_dataModel[7]);
        case 0x09:
        return QString("%2").arg(m_dataModel[8]);
        /*电流有效值*/
        case 0x0a:
        return QString("%2").arg(m_dataModel[9]);
        case 0x0b:
        return QString("%2").arg(m_dataModel[10]);
        case 0x0c:
        return QString("%2").arg(m_dataModel[11]);
        case 0x0d:
        return QString("%2").arg(m_dataModel[12]);
        //频率
        case 0x0e:
        return QString("%2").arg(m_dataModel[13]);
        /*有功功率*/
        case 0x0f:
        return QString("%2").arg(m_dataModel[14]);
        case 0x10:
        return QString("%2").arg(m_dataModel[15]);
        case 0x11:
        return QString("%2").arg(m_dataModel[16]);
        case 0x12:
        return QString("%2").arg(m_dataModel[17]);
        /*矢量电压和有效值*/
        case 0x13:
        return QString("%2").arg(m_dataModel[18]);
        case 0x14:
        return QString("%2").arg(m_dataModel[19]);
        /*基波功率*/
        case 0x16:
        return QString("%2").arg(m_dataModel[20]);
        case 0x17:
        return QString("%2").arg(m_dataModel[21]);
        case 0x18:
        return QString("%2").arg(m_dataModel[22]);
        case 0x19:
        return QString("%2").arg(m_dataModel[23]);
        /*基波dianneng*/
        case 0x1a:
        return QString("%2").arg(m_dataModel[24]);
        case 0x1b:
        return QString("%2").arg(m_dataModel[25]);
        case 0x1c:
        return QString("%2").arg(m_dataModel[26]);
        case 0x1d:
        return QString("%2").arg(m_dataModel[27]);
        /*无功功率*/
        case 0x1e:
        return QString("%2").arg(m_dataModel[28]);
        case 0x1f:
        return QString("%2").arg(m_dataModel[29]);
        case 0x20:
        return QString("%2").arg(m_dataModel[30]);
        case 0x21:
        return QString("%2").arg(m_dataModel[31]);
        /*视在功率*/
        case 0x22:
        return QString("%2").arg(m_dataModel[32]);
        case 0x23:
        return QString("%2").arg(m_dataModel[33]);
        case 0x24:
        return QString("%2").arg(m_dataModel[34]);
        case 0x25:
        return QString("%2").arg(m_dataModel[35]);
        /*功率因数*/
        case 0x26:
        return QString("%2").arg(m_dataModel[36]);
        case 0x27:
        return QString("%2").arg(m_dataModel[37]);
        case 0x28:
        return QString("%2").arg(m_dataModel[38]);
        case 0x29:
        return QString("%2").arg(m_dataModel[39]);
        /*有功电能*/
        case 0x2a:
        return QString("%2").arg(m_dataModel[40]);
        case 0x2b:
        return QString("%2").arg(m_dataModel[41]);
        case 0x2c:
        return QString("%2").arg(m_dataModel[42]);
        case 0x2d:
        return QString("%2").arg(m_dataModel[43]);
        /*视在电能*/
        case 0x2f:
        return QString("%2").arg(m_dataModel[44]);
        case 0x30:
        return QString("%2").arg(m_dataModel[45]);
        case 0x31:
        return QString("%2").arg(m_dataModel[46]);
        case 0x32:
        return QString("%2").arg(m_dataModel[47]);
        /*芯片温度*/
        case 0x33:
        return QString("%2").arg(m_dataModel[48]);

    default:
        return "null";
    }
}
