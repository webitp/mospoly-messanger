#include "serverfunctions.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>


QString ServerFunctions::auth(QStringList auth_list){
   /* DataBase::getInstance();
    QSqlQuery query_auth = DataBase::query();
    query_auth.prepare("select * from public.users where password= :password and phone= :phone and username= :username");
    query_auth.bindValue(":username", auth_list.at(0));
    query_auth.bindValue(":password", auth_list.at(1));
    query_auth.bindValue(":phone", auth_list.at(2));
    query_auth.exec();
    if(query_auth.isNull(false)){
        return "there are no user with those parametrs";
    }else{ */
        return "auth success";
  //  }


}

QString ServerFunctions::reg(QStringList reg_list){
   /* DataBase::getInstance();
    QSqlQuery query_reg = DataBase::query();
    query_reg.prepare("insert into public.users(password, phone, username, online) values (:pass, :phone, :name, :online)");
    query_reg.bindValue(":name", reg_list.at(0));
    query_reg.bindValue(":pass", reg_list.at(1));
    query_reg.bindValue(":phone", reg_list.at(2));
    query_reg.bindValue(":online", "true");
    query_reg.exec(); */
    return "register success";
}

QString ServerFunctions::parse(QString query)
{
    query = query.trimmed();
    QStringList params = query.split(QLatin1Char('&'));
    QString function = params.front();
    params.pop_front();

    if (function == "auth")
        return auth(params);
    if (function == "reg")
        return reg(params);

    return "";
}

