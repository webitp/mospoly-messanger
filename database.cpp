#include "database.h"

Database::Database()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(DB_HOST);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USER);
    db.setPassword(DB_PASSWORD);

    if (db.open())
        qDebug() << "[DB] Database connected!";
    else
        throw "[DB] Database connection refused!";
}
