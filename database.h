#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QDebug>

class DatabaseDestroyer1;

class Database1
{
public:
    friend class DatabaseDestroyer1;
private:
    static Database1* p_instance;
    static DatabaseDestroyer1 destroyer;

    const QString DB_HOST = "localhost";
    const QString DB_NAME = "mospoly_messanger";
    const QString DB_USER = "root";
    const QString DB_PASSWORD = "";

    QSqlDatabase db;
    static int qwe;
protected:
    Database1();
    Database1(const Database1&) = delete;
    Database1& operator = (Database1 &) = delete;
    ~Database1(){};


public:
    static Database1* getInstance();
   /* {
        if (p_instance==nullptr)
        {
            p_instance = new Database1();
            //destroyer.initialize(p_instance);
        }
        return p_instance;
    }*/
};

class DatabaseDestroyer1
{
    private:
        Database1* p_instance1=nullptr;
    public:
        DatabaseDestroyer1(){};
        ~DatabaseDestroyer1(){if(p_instance1 != nullptr) delete p_instance1;};
        void initialize(Database1 * p){ p_instance1 = p; }
};

#endif // DATABASE_H
