#ifndef SYS_INFO_H
#define SYS_INFO_H

#include <QObject>

class SysInfo : public QObject
{
    Q_OBJECT
public:
    explicit SysInfo(QObject *parent = nullptr);

signals:

};

#endif // SYS_INFO_H
