#include <QCoreApplication>
#include "sysinfo.h"
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SysInfo sysinfo(&a);
    TCPServer tcpserv(&a);
    tcpserv.startServer(5770);

    return a.exec();
}
