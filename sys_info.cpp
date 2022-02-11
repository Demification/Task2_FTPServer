#include "sys_info.h"
#include <QDebug>
#include <QSysInfo>

SysInfo::SysInfo(QObject *parent)
    : QObject{parent}
{
    qInfo() << "CPU Arch: " << QSysInfo::currentCpuArchitecture();
    qInfo() << "OS Name: " << QSysInfo::prettyProductName();
}
