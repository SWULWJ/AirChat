#include <QThread>

#include "ChatBusiness.h"
#include "MyTcpSocket.h"

ChatBusiness::ChatBusiness(QObject *parent)
    : QObject{parent}
{

}

void ChatBusiness::mainBusiness(qintptr handle)
{
    MyTcpSocket *tcpSocket = new MyTcpSocket(this, handle);
    connect(tcpSocket, &MyTcpSocket::registerSignal, this, &ChatBusiness::socketRegisterHandle);
    connect(tcpSocket, &MyTcpSocket::forwardSignal, this, &ChatBusiness::socketForwardHandle);
    connect(this, &ChatBusiness::registerSuccessedSiganl, tcpSocket, &MyTcpSocket::registerSuccessedHandle);
    connect(this, &ChatBusiness::registerFailedSiganl, tcpSocket, &MyTcpSocket::registerFailedHandle);
    connect(this, &ChatBusiness::sendSiganl, tcpSocket, &MyTcpSocket::sendHandle);
    connect(this, &ChatBusiness::sendFailedSiganl, tcpSocket, &MyTcpSocket::sendFailedHandle);
    connect(tcpSocket, &MyTcpSocket::disconnectedSiganl, this, &ChatBusiness::disconnectedHandle);
    tcpSocket->setSocketDescriptor(handle);
}

void ChatBusiness::socketRegisterHandle(QString userName, qintptr handle)
{
    emit registerSiganl(userName, handle);
}

void ChatBusiness::socketForwardHandle(QString targetName, QString mesg)
{
    emit forwardSiganl(targetName, mesg);
}

void ChatBusiness::disconnectedHandle(QString userName, qintptr handle)
{
    emit removeAndClose(userName, handle);
    qDebug() << "disconnectedHandle";
}
