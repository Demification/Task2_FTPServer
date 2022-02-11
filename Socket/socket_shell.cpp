#include "socket_shell.h"

SocketShell::SocketShell(QObject *parent)
    : QTcpSocket{parent}
{
    static int i = 0;
    myName = "Socket-" + QString::number(i);
}

QString SocketShell::getMyName()
{
    return myName;
}

void SocketShell::readyReadSlot()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_5_15);

    if(in.status() == QDataStream::Ok)
    {
        in.startTransaction();

        readData.clear();
        in >> readData;

        if (in.commitTransaction())
        {
            qInfo() << myName << " read " << readData.length() << "bytes";
            emit alreadyRead(readData);
        }
    }
    else
        qWarning() << myName << " can`t read data !";
}
