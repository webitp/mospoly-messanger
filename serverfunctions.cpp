#include "serverfunctions.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QDateTime>


QString ServerFunctions::auth(QStringList auth_list){
    DataBase::getInstance();
    QSqlQuery query_auth = DataBase::query();
    query_auth.prepare("select * from public.users where password= :password and username= :username order by id desc limit 1");
    query_auth.bindValue(":username", auth_list.at(0));
    query_auth.bindValue(":password", auth_list.at(1));
    query_auth.exec();
    query_auth.first();
    QSqlRecord rec1 = query_auth.record();


    if(!query_auth.isValid()){
        return "there are no user with those parametrs";
    }else{
        const int id_Index = rec1.indexOf("id");
        int id = query_auth.value(id_Index).toInt();
        qint64 create_time = QDateTime::currentSecsSinceEpoch();
        QDateTime create_date = QDateTime::currentDateTime();
        QDateTime expired_date = create_date.addYears(1);
        size_t token = qHash(create_time);
        QString token_16 = QString::number(token, 16);
        query_auth.prepare("insert into public.user_tokens(user_id, token, expired_at) values (:user_id, :token, :expired_at)");
        query_auth.bindValue(":user_id", id);
        query_auth.bindValue(":token", token_16);
        query_auth.bindValue(":expired_at", expired_date);
        query_auth.exec();
        //qDebug()<<query_auth.exec("insert into public.user_tokens(user_id, token) values (3, 'laskdj')");
        return token_16;
    };
}

QString ServerFunctions::reg(QStringList reg_list){
    DataBase::getInstance();
    QSqlQuery query_reg = DataBase::query();
    query_reg.prepare("insert into public.users(password, phone, username, online) values (:pass, :phone, :name, :online)");
    query_reg.bindValue(":name", reg_list.at(0));
    query_reg.bindValue(":pass", reg_list.at(1));
    query_reg.bindValue(":phone", reg_list.at(2));
    query_reg.bindValue(":online", "true");
    query_reg.exec();

    query_reg.exec("select * from public.users order by id desc limit 1");
    QSqlRecord rec = query_reg.record();
    const int username_Index = rec.indexOf("username");
    const int password_Index = rec.indexOf("password");

    while(query_reg.next())
        qDebug()<<query_reg.value(username_Index).toString()
               <<"\t"<<query_reg.value(password_Index).toString()<<"\n";

    return auth(reg_list);
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

