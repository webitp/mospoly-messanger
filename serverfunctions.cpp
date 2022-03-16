#include "serverfunctions.h"

QString ServerFunctions::parse(QString query)
{
    query = query.trimmed();
    QStringList params = query.split(QLatin1Char('&'));
    QString function = params.front();
    params.pop_front();

    if (function == "auth")
        return auth(params.at(0),params.at(1));
    if (function == "reg")
        return reg(params.at(0),params.at(1));

    return "";
}
QString ServerFunctions::auth(QString login, QString password){
    return "auth finished";
}
QString ServerFunctions::reg(QString login, QString password){
    return "register finished";
}
