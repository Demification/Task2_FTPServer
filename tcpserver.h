#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QVector>
#include <QTime>
#include <QMutex>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>

class Client : public QThread
{
    Q_OBJECT

    QTcpSocket *socket;
    qintptr socketDescriptor;

    QString getMyName();

public:
    explicit Client(qintptr socketDescriptor, QObject *parent = nullptr);

    void run() override;
    void sendToClient(QString str);

signals:

public slots:
    void readyRead();
    void disconnected();

};

class TCPServer : public QTcpServer
{
    Q_OBJECT
    QVector<Client*> clients;
    QMutex delClientMutex;

protected:
    void incomingConnection(qintptr socketDescriptor) override;

public:
    explicit TCPServer(QObject *parent = nullptr);

    void startServer(quint16 port);

signals:

public slots:
    void delClient(Client* client);

};

#endif // TCPSERVER_H
