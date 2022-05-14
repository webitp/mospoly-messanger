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
    {
        qDebug() << "[DB] Database connected!";
    }
    else
    {
        qDebug() << "[DB] Database connection refused!";
        qDebug() << db.lastError().text();
    }
    QSqlQuery query_users(db);
    query_users.exec("CREATE TABLE IF NOT EXISTS public.users("
                         "id serial, "
                         "password varchar(256), "
                         "phone text COLLATE pg_catalog.\"default\" NOT NULL, "
                         "username text COLLATE pg_catalog.\"default\", "
                         "online boolean DEFAULT false, "
                         "created_at timestamp with time zone DEFAULT CURRENT_TIMESTAMP, "
                         "CONSTRAINT users_pkey PRIMARY KEY (id));");
    query_users.exec("ALTER TABLE IF EXISTS public.users"
                         "OWNER to postgres;");
   // query_users.exec("CREATE TABLE IF NOT EXISTS public.users(id serial,password varchar(256),phone text COLLATE pg_catalog.\"default\" NOT NULL,username text COLLATE pg_catalog.\"default\", online boolean DEFAULT false,created_at timestamp with time zone DEFAULT CURRENT_TIMESTAMP,CONSTRAINT users_pkey PRIMARY KEY (id));ALTER TABLE IF EXISTS public.users OWNER to postgres;");
    query_users.exec("CREATE TABLE public.user_tokens("
                         "id integer, "
                         "user_id integer NOT NULL, "
                         "token text NOT NULL, "
                         "expired_at timestamp with time zone, "
                         "created_at timestamp with time zone DEFAULT CURRENT_TIMESTAMP, "
                         "PRIMARY KEY (id));");
    query_users.exec("ALTER TABLE IF EXISTS public.user_tokens"
                         "OWNER to postgres;");

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

QSqlQuery DataBase::query()
{
    getInstance();
    QSqlQuery query;
    return query;
}
