#include "tcp_server.h"
#include <QDataStream>

TCPServer::TCPServer(QObject *parent)
    : QTcpServer(parent)
{

}

TCPServer::~TCPServer()
{
    for(auto client: clients)
        client->disconnected();
}

void TCPServer::startServer(quint16 port)
{
    if(listen(QHostAddress::Any, port))
         qInfo() << "TCPServer start:" << this->serverAddress() << " port:" << port;
    else
    {
        qCritical() << "TCPServer not listen!!!";
        close();
    }
}

void TCPServer::delClient(SocketShell *client)
{
    delClientMutex.lock();

    auto it = std::find(clients.begin(), clients.end(), client);
    if(it != clients.end())
    {
        clients.erase(it);
        qDebug() << "Delete client " << it << ".";
    }
    else
        qWarning() << "Client not found!!!";

    delClientMutex.unlock();
}
