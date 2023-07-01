#include <QCoreApplication>

#include "MyTcpServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer tcpServer;
    tcpServer.listen(QHostAddress::Any, quint16(8848));

    return a.exec();
}
