#ifndef MAIN_H
#define MAIN_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebView/QtWebView>
#include <QString>
#include <QDir>
#include <QtCore/QUrl>
#include <QtQml/QQmlContext>

#endif // MAIN_H

namespace config
{
    const bool DEBUG = true;

    const QString DEVELOPMENT_PATH = "http://127.0.0.1:8080/";
    const QString PRODUCTION_PATH = "file:///" + QDir::currentPath() +"/debug/webview/index.html";
}
