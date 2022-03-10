#include "server.h"
#include "serverfunctions.h"
#include <sstream>
#include <QDebug>
#include <QCoreApplication>
#include <QAbstractSocket>


Server::~Server()
{
    _server->close();
}

Server::Server(QObject *parent) : QObject(parent){
    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection,
            this, &Server::slotNewConnection);

    if(!_server->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void Server::slotNewConnection(){
    QTcpSocket *clientSocket = _server->nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(slotServerRead()));
    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(slotSocketStateChanged(QAbstractSocket::SocketState)));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(slotClientDisconnected()));

    Client client = Client();
    _sockets.insert(clientSocket, client);
    qDebug() << QByteArray::fromStdString(clientSocket->peerAddress().toString().toStdString() + " connected to server!");
}

void Server::slotSocketStateChanged(QAbstractSocket::SocketState socketState) {
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _sockets.take(sender);
    }
}


void Server::slotServerRead(){
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());

    while (sender->canReadLine())
    {
        // в клиенте будет содержаться текущий юзер, если он авторизован
        Client client = _sockets.value(sender);
        QString query_str = QString(sender->readLine());
        QString response = ServerFunctions::parse(query_str);
        sender->write(response.toUtf8());
    }
}

void Server::slotClientDisconnected(){
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    _sockets.take(sender);
    qDebug() << QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + " disconnected from server!");
}
