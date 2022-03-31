#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

class Client
{
public:
    Client();

    bool is_auth = false;
private:
    QString _token;
};

#endif // CLIENT_H
