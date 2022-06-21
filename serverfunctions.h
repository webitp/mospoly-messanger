#include "QString"
#include <QStringList>
#include <QDebug>

namespace ServerFunctions {
    QString parse(QString query);
    QString auth(QStringList auth_list);
    QString reg(QStringList reg_list);
    QString authentication(QStringList authentication_list);
    QString message(QStringList message_list);
    QString history(QStringList history_list);
}
