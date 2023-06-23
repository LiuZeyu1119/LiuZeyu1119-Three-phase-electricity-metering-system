#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include "sensordata/sensordata.h"
#include "wireless/wireless.h"
#include "timeset/timeset.h"
#include "topbar.h"
#include "sqlite/sqlite.h"
int main(int argc, char *argv[])
{

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    sensordata sensorOBJ;
    sqlite sqliteOBJ;
    QQuickView view;
    //QQmlContext *ctxt = view.rootContext();
    sqliteOBJ.refreshList();
    //ctxt->setContextProperty("dataModel", QVariant::fromValue(sqliteOBJ.dataList));
    engine.rootContext()->setContextProperty("sqlitOBJ",&sqliteOBJ);

    engine.rootContext()->setContextProperty("sensorOBJ",&sensorOBJ);

    qmlRegisterType<detcMoveToThread>("detcMoveToThread",1,0,"DetcMoveToThread");
    qmlRegisterType<sensordata>("sensorData",1,0,"SensorDataModel");
    qmlRegisterType<wirelessListModel>("wirelessModel", 1, 0, "WirelessListModel");
    qmlRegisterType<timeSet>("timeSet",1,0,"TimesetModel");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    engine.setOfflineStoragePath("./");  //设置数据库存储路径
    return app.exec();
}
