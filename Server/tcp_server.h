#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QObject>
#include <QVector>
#include <QMutex>
#include <QTcpServer>
#include <Socket/socket_shell.h>

class TCPServer : public QTcpServer
{
    Q_OBJECT
    QMutex delClientMutex;

protected:
    QVector<SocketShell*> clients;

public:
    explicit TCPServer(QObject *parent = nullptr);

    virtual ~TCPServer();

    void startServer(quint16 port);

signals:

public slots:
    void delClient(SocketShell* client);

};

#endif // TCP_SERVER_H
