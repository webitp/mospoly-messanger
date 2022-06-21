#ifndef SERVER_H
#define SERVER_H
#include "client.h"
#include <string>
#include <vector>
#include <QObject>
#include <QMap>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotSocketStateChanged(QAbstractSocket::SocketState socketState);

    void slotServerRead();
private:
    QTcpServer* _server;
    QMap<QTcpSocket*, Client>  _sockets;
};
#endif // SERVER_H
