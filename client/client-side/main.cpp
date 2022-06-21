#include "main.h"
#include <qwebview_global.h>
#include <QVariant>
#include <QtQuick>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QtWebView::initialize();
    QGuiApplication app(argc, argv);

    const QString initialUrl = config::DEBUG ? config::DEVELOPMENT_PATH : config::PRODUCTION_PATH;

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    qDebug() << initialUrl;

    context->setContextProperty(QStringLiteral("initialUrl"), initialUrl);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
        qDebug() << obj->children()[1];
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
