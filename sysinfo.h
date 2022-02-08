#ifndef SYSINFO_H
#define SYSINFO_H

#include <QObject>

class SysInfo : public QObject
{
    Q_OBJECT
public:
    explicit SysInfo(QObject *parent = nullptr);

signals:

};

#endif // SYSINFO_H
