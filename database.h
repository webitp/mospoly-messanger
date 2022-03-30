#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QDebug>

class DatabaseDestroyer;

class DataBase
{
public:
    friend class DatabaseDestroyer;
private:
    static DataBase* p_instance;
    static DatabaseDestroyer destroyer;

    const QString DB_HOST = "127.0.0.1";
    const QString DB_NAME = "postgres";
    const QString DB_USER = "postgres";
    const QString DB_PASSWORD = "postgres";
    const int DB_PORT = 5432;

    QSqlDatabase db;
    static int qwe;
protected:
    DataBase();
    DataBase(const DataBase&) = delete;
    DataBase& operator = (DataBase &) = delete;
    ~DataBase(){};


public:
    static DataBase* getInstance();
   /* {
        if (p_instance==nullptr)
        {
            p_instance = new Database1();
            //destroyer.initialize(p_instance);
        }
        return p_instance;
    }*/
};

class DatabaseDestroyer
{
    private:
        DataBase* p_instance=nullptr;
    public:
        DatabaseDestroyer(){};
        ~DatabaseDestroyer(){if(p_instance != nullptr) delete p_instance;};
        void initialize(DataBase * p){ p_instance = p; }
};

#endif // DATABASE_H
