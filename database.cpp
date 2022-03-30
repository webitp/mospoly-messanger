#include "database.h"

DataBase* DataBase::p_instance = nullptr;
DatabaseDestroyer DataBase::destroyer;

DataBase::DataBase()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(DB_HOST);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USER);
    db.setPassword(DB_PASSWORD);
    db.setPort(DB_PORT);

    if (db.open())
        qDebug() << "[DB] Database connected!";
    else
        qDebug() << "[DB] Database connection refused!";
}

DataBase* DataBase::getInstance()
{
    if (!p_instance)
    {
        p_instance = new DataBase();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

