#include "ftp_socket_shell.h"

#include <QFile>
#include <QDirIterator>
#include <QTextCodec>
#include <QMetaEnum>

#include "Server/tcp_server.h"

QString FTPSocketShell::getMyName()
{
    return "FTPSocket" + QString::number(socketDescriptor);
}

FTPSocketShell::FTP_COMMANDS FTPSocketShell::dataToCommand(const QByteArray &data)
{
    QString str_command = dataToString(data);
    return stringToCommand(str_command);
}

FTPSocketShell::FTP_COMMANDS FTPSocketShell::stringToCommand(const QString &str)
{
    auto&& metaEnum = QMetaEnum::fromType<FTP_COMMANDS>();
    for(int i = 0; i < metaEnum.keyCount(); i++)
    {
        FTP_COMMANDS value = (FTP_COMMANDS)metaEnum.value(i);
        if(str == QVariant::fromValue(value).toString())
            return value;
    }
    return FTP_COMMANDS::ERR;
}

QString FTPSocketShell::dataToString(const QByteArray &data)
{
    QString str;
        for(auto a: data.toStdString())
            if(a != '\0')
                str.append(a);
        return str;
}

FTPSocketShell::FTPSocketShell(const qintptr socketDescriptor, QObject *parent)
    : QThread{parent}, socketDescriptor{socketDescriptor}
{

}

void FTPSocketShell::run()
{
    socket = new SocketShell();

    if(socket->setSocketDescriptor(socketDescriptor))
    {
        connect(socket, &QTcpSocket::disconnected, this, &FTPSocketShell::disconnectedSlot);
        connect(socket, &QTcpSocket::readyRead, socket, &SocketShell::readyReadSlot, Qt::DirectConnection);
        connect(socket, &SocketShell::alreadyRead, this, &FTPSocketShell::alreadyReadSlot, Qt::DirectConnection);
        qDebug() << getMyName() << " is run.";
        exec();
    }
    else
        qWarning() << getMyName() << " not run!";
}

SocketShell *FTPSocketShell::getSocket()
{
    return socket;
}

void FTPSocketShell::disconnectedSlot()
{
    qInfo() << getMyName() << " is disconnected.";
    ((TCPServer*)parent())->delClient(socket);
    socket->deleteLater();
    exit(0);
}

void FTPSocketShell::alreadyReadSlot(const QByteArray &data)
{
    auto line = dataToString(data).split('/');
    auto str_command = line[0];
    auto str_param = line[1];

    FTP_COMMANDS command = stringToCommand(str_command);

    switch (command)
    {
        case GET:
        {
        QString filepath = QDir::currentPath() + "/" + str_param;
        qDebug() << "filepath: " << filepath;
        QFile file(filepath);
        if(file.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            QByteArray filedata = file.readAll();
            socket->write(filedata);

            int msec = 10000;
            socket->waitForBytesWritten(msec);
            qDebug() << "Send " << filedata.length() << "bytes";

            socket->close();
        }
        break;
        }
        default:
        {
            command = ERR;
            break;
        }
    };

}
