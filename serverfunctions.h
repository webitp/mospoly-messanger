#include "QString"
#include <QStringList>
#include <QDebug>

namespace ServerFunctions {
    QString parse(QString query);
    QString auth(QStringList auth_list);
    QString reg(QStringList reg_list);
    QString token(QStringList token_list);
}
