#ifndef FTPSOCKETSHELL_H
#define FTPSOCKETSHELL_H

#include <QObject>
#include <QThread>

#include "socket_shell.h"

class FTPSocketShell: public QThread
{
public:
    enum FTP_COMMANDS { GET, ERR};
    Q_ENUM(FTP_COMMANDS);

private:
    Q_OBJECT
    const qintptr socketDescriptor;
    SocketShell* socket = nullptr;

    QString getMyName();
    FTP_COMMANDS dataToCommand(const QByteArray &data);
    FTP_COMMANDS stringToCommand(const QString& str);
    QString dataToString(const QByteArray &data);

public:
    explicit FTPSocketShell(const qintptr socketDescriptor, QObject *parent = nullptr);

    void run() override;

    SocketShell* getSocket();

signals:

public slots:
    void disconnectedSlot();
    void alreadyReadSlot(const QByteArray &data);
};

#endif // FTPSOCKETSHELL_H
