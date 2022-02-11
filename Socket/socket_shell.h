#ifndef SOCKET_SHELL_H
#define SOCKET_SHELL_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

class SocketShell: public QTcpSocket
{
    Q_OBJECT
    QByteArray readData;
    QString myName;

public:
    explicit SocketShell(QObject *parent = nullptr);

    QString getMyName();

    template<typename T> void send(T var)
    {
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_15);
        out << var;
        write(data);

        int msec = 10000;
        waitForBytesWritten(msec);
    }

signals:
    void alreadyRead(const QByteArray& data);

public slots:
    void readyReadSlot();

};

#endif // SOCKET_SHELL_H
