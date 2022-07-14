#include "serverfunctions.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>


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

QString ServerFunctions::authentication(QStringList authentication_list){
    DataBase::getInstance();
    QSqlQuery query_authentication = DataBase::query();
    query_authentication.prepare("select users.id, username, phone from public.users join public.user_tokens on users.id=user_tokens.user_id where token= :token");
    query_authentication.bindValue(":token", authentication_list.at(0));
    query_authentication.exec();
    query_authentication.first();
    QSqlRecord authen_rec = query_authentication.record();

    if(query_authentication.isValid()){
        QJsonObject data;
        data.insert("user_id", QJsonValue::fromVariant(query_authentication.value(0).toString()));
        data.insert("username", QJsonValue::fromVariant(query_authentication.value(1).toString()));
        data.insert("phone", QJsonValue::fromVariant(query_authentication.value(2).toString()));
        QJsonDocument doc(data);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
     // qDebug()<<jsonString;
        return jsonString;
    }else{
        return "token is not founded";
    }
}

QString ServerFunctions::message(QStringList message_list)
{
    DataBase::getInstance();
    QSqlQuery query_message = DataBase::query();
    query_message.prepare("insert into public.messages(user1_id, user2_id, message) values (:user1, :user2, :message)");
    query_message.bindValue(":user1", message_list.at(0));
    query_message.bindValue(":user2", message_list.at(1));
    query_message.bindValue(":message", message_list.at(2));
    query_message.exec();
    return "message is added";
}
QString ServerFunctions::history(QStringList history_list)
{
    QJsonObject jsonObj;
    QSqlQuery history_query = DataBase::query();
    history_query.prepare("select user1_id, user2_id, created_at, message from messages where (user1_id= :us1_id or user1_id= :us2_id) and (user2_id=:us1_id or user2_id=:us2_id) order by created_at");
    history_query.bindValue(":us1_id", history_list.at(0));
    history_query.bindValue(":us2_id", history_list.at(1));
    history_query.exec();
    int cnt_mes=1;
    int cnt =0;
    while (history_query.next())
    {
        cnt=0;
        QJsonObject jsonObj_mes;
        jsonObj_mes.insert("user1_id", QJsonValue::fromVariant(history_query.value(cnt++).toString()));
        jsonObj_mes.insert("user2_id", QJsonValue::fromVariant(history_query.value(cnt++).toString()));
        jsonObj_mes.insert("created_at", QJsonValue::fromVariant(history_query.value(cnt++).toString()));
        jsonObj_mes.insert("message", QJsonValue::fromVariant(history_query.value(cnt++).toString()));
        QString count_mes = QString::number(cnt_mes++);
        jsonObj.insert("message " + count_mes, jsonObj_mes);
    }
    QJsonDocument doc(jsonObj);
    QString jsonString = doc.toJson(QJsonDocument::Indented);
    return jsonString;
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
    if (function == "authentication")
        return authentication(params);
    if (function == "message")
        return message(params);
    if (function == "history")
        return history(params);
    return "";
}


