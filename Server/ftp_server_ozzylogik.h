#ifndef FTPSERVEROZZYLOGIK_H
#define FTPSERVEROZZYLOGIK_H

#include <QObject>

#include "tcp_server.h"

class FTPServerOzzylogik : public TCPServer
{
    Q_OBJECT

public:
    explicit FTPServerOzzylogik(QObject *parent = nullptr);

    void incomingConnection(qintptr socketDescriptor) override;

signals:

};

#endif // FTPSERVEROZZYLOGIK_H
