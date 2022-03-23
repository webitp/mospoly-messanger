#include <QSqlDatabase>
#include <QString>
#include <QDebug>

#ifndef DATABASE_H
#define DATABASE_H

class Database;

class DatabaseDestroyer
{
    private:
        Database* p_instance;
    public:
        ~DatabaseDestroyer();
        void initialize(Database * p){ p_instance = p; }
};

class Database
{
private:
    static Database* p_instance;
    static DatabaseDestroyer destroyer;

    const QString DB_HOST = "localhost";
    const QString DB_NAME = "mospoly_messanger";
    const QString DB_USER = "root";
    const QString DB_PASSWORD = "";

protected:
    Database();
    Database(const Database&);
    Database& operator = (Database &);
    ~Database();
    friend class DatabaseDestroyer;

public:
    static Database* getInstance(){
        if (!p_instance)
        {
            p_instance = new Database();
            destroyer.initialize(p_instance);
        }
        return p_instance;
    }
};

#endif // DATABASE_H
