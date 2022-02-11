#include "ftp_server_ozzylogik.h"

#include "Socket/ftp_socket_shell.h"

FTPServerOzzylogik::FTPServerOzzylogik(QObject *parent)
    : TCPServer{parent}
{

}

void FTPServerOzzylogik::incomingConnection(qintptr socketDescriptor)
{
    FTPSocketShell* socket = new FTPSocketShell(socketDescriptor, this);
    socket->start();
    while (!socket->getSocket())
        QThread::currentThread()->usleep(true);

    clients.push_back(socket->getSocket());
}
