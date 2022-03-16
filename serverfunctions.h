#include "QString"
#include <QStringList>
#include <QDebug>

namespace ServerFunctions {
    QString parse(QString query);
    QString auth(QString login, QString password);
    QString reg(QString login, QString password);
}
