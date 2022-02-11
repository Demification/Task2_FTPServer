#include <QCoreApplication>
#include "sys_info.h"
#include "Server/ftp_server_ozzylogik.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SysInfo sysinfo(&a);
    FTPServerOzzylogik tcpserv(&a);
    tcpserv.startServer(5770);

    return a.exec();
}
