#include "database.h"

Database1* Database1::p_instance = nullptr;
DatabaseDestroyer1 Database1::destroyer;

Database1::Database1()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(DB_HOST);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USER);
    db.setPassword(DB_PASSWORD);

    if (db.open())
        qDebug() << "[DB] Database connected!";
    else
        throw "[DB] Database connection refused!";
}

Database1* Database1::getInstance()
{
    if (!p_instance)
    {
        p_instance = new Database1();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

