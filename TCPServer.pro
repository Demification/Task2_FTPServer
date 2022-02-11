QT -= gui
QT += core network sql

CONFIG += c++14 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Server/ftp_server_ozzylogik.cpp \
        Server/tcp_server.cpp \
        Socket/ftp_socket_shell.cpp \
        Socket/socket_shell.cpp \
        main.cpp \
        sys_info.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Server/ftp_server_ozzylogik.h \
    Server/tcp_server.h \
    Socket/ftp_socket_shell.h \
    Socket/socket_shell.h \
    sys_info.h
