#include "ChatBusiness.h"
#include "MyTcpSocket.h"

ChatBusiness::ChatBusiness(QObject *parent)
    : QObject{parent}
{

}

void ChatBusiness::run(qintptr handle)
{
    MyTcpSocket *tcpSocket = new MyTcpSocket(this);

    connect(tcpSocket, &MyTcpSocket::signInSucSignal, this, &ChatBusiness::signInSucHandle);
    connect(tcpSocket, &MyTcpSocket::forwardMesgProcess, this, &ChatBusiness::forwardMesgHandle);
    connect(this, &ChatBusiness::sendMesgSignal, tcpSocket, &MyTcpSocket::sendMesgHandle);
    connect(tcpSocket, &MyTcpSocket::newFriendSignal, this, &ChatBusiness::forwardMesgHandle);
    connect(tcpSocket, &MyTcpSocket::disconnectedSignal, this, &ChatBusiness::disconnectedHandle);

    tcpSocket->myHandle = handle;
    tcpSocket->setSocketDescriptor(handle);
}

void ChatBusiness::signInSucHandle(QString account, qintptr handle)
{
    emit signInSucSignal(account, handle);
}

void ChatBusiness::forwardMesgHandle(QString toAccount, QString mesg)
{
    emit forwardMesgSignal(toAccount, mesg);
}

void ChatBusiness::disconnectedHandle(QString account, qintptr handle)
{
    emit disconnectedSignal(account, handle);
}
