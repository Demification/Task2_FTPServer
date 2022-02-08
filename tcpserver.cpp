#include "tcpserver.h"
#include <QDataStream>

QString Client::getMyName()
{
    return "Client-" + QString::number(socketDescriptor);
}

Client::Client(qintptr socketDescriptor, QObject *parent)
    : QThread{parent}, socketDescriptor{socketDescriptor}
{

}

void Client::run()
{
    if(socket->setSocketDescriptor(this->socketDescriptor))
    {
        connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected);
        connect(socket,  &QTcpSocket::readyRead, this, &Client::readyRead, Qt::DirectConnection);

        qInfo() << getMyName() << " is run.";
        exec();
    }
    else
        qWarning() << getMyName() << " not run! " << socket->error();
}

void Client::readyRead()
{
    QDataStream stream(socket);
    stream.setVersion(QDataStream::Qt_5_15);

    if(stream.status() == QDataStream::Ok)
    {
        QString str;
        stream >> str;
        qInfo() << str;
    }
    else
        qWarning() << "Client can`t read data !";
}

void Client::sendToClient(QString str)
{
    QByteArray data;
    QDataStream stream(data);
    stream.setVersion(QDataStream::Qt_5_15);
    stream << str;

    socket->write(data);
    qInfo() << getMyName() << " is wrote: " << str;
}

void Client::disconnected()
{
    qInfo() << getMyName() << " is disconnected.";
    ((TCPServer*)parent())->delClient(this);
    socket->deleteLater();
    exit(0);
}

TCPServer::TCPServer(QObject *parent)
    : QTcpServer{parent}
{

}

void TCPServer::startServer(quint16 port)
{
    if(listen(QHostAddress::AnyIPv4, port))
         qInfo() << "Start server.";
    else
    {
        qCritical() << "TCPServer not listen!!!";
        close();
    }
}

void TCPServer::incomingConnection(qintptr socketDescriptor)
{
    Client* client = new Client(socketDescriptor, this);
    clients.push_back(client);

    client->start();

    qInfo() << "New client incoming...";
}

void TCPServer::delClient(Client *client)
{
    delClientMutex.lock();

    auto it = std::find(clients.begin(), clients.end(), client);
    if(it != clients.end())
    {
        clients.erase(it);
        qInfo() << "Delete client.";
    }
    else
        qWarning() << "Client not found!!!";

    delClientMutex.unlock();
}
