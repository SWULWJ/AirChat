#include "MyTcpSocket.h"
#include <QHostAddress>

MyTcpSocket::MyTcpSocket(QObject *parent)
    : QTcpSocket{parent}
{
    isConnected = false;
    connect(this, &MyTcpSocket::readyRead, this, &MyTcpSocket::readyReadHandle);
    connect(this, &MyTcpSocket::connected, [=](){isConnected = true;});
}

void MyTcpSocket::init(QString ip, quint16 port)
{
    this->serverIP = ip;
    this->serverPort = port;
}

void MyTcpSocket::readyReadHandle()
{
    QString mesg = this->readAll();
    emit newMesg(mesg);
}

void MyTcpSocket::disconnectedHandle()
{
    isConnected = false;
}

void MyTcpSocket::sendHandle(char* mesg)
{
    if(isConnected != true)
    {
        this->connectToHost(QHostAddress(serverIP), serverPort);
    }
    this->write(mesg);

}
