#include <QCoreApplication>

#include "MyTcpServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer *tcpServer = new MyTcpServer();
    tcpServer->listen(QHostAddress::Any, quint16(0000));

    return a.exec();
}
