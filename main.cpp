#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QqmlContext>
#include "database.h"
#include "listmodel.h"



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");
    DataBase database;
    database.connectToDataBase();
    ListModel *model = new ListModel();


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("myModel", model);
    engine.rootContext()->setContextProperty("database", &database);

    const QUrl url(u"qrc:/lab4/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);



    return app.exec();
}
