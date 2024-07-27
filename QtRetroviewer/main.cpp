#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include "backend.h"
#include "imageProvider.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN) && QT_VERSION_CHECK(5, 6, 0) <= QT_VERSION && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    /* Backend C++ connection to QML */
    qmlRegisterType<Backend>("comm.retroviewer.backend", 1, 0, "Backend");
    //Backend* backend = new Backend();
    //backend->testMessage("TEST SUCCESSFUL");
    //engine.rootContext()->setContextProperty("Backend", backend);
    /*--------------------*/

    //Image Provider
    imageProvider* imgProvider = new imageProvider();
    engine.addImageProvider("dynamic", imgProvider);

    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/qtretroviewer/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
