#include "MyTcpSocket.h"

MyTcpSocket::MyTcpSocket(QObject *parent, qintptr handle)
    : QTcpSocket{parent}
{
    this->handle = handle;
    connect(this, &MyTcpSocket::readyRead, this, &MyTcpSocket::readyReadHandle);
    connect(this, &MyTcpSocket::disconnected, this, &MyTcpSocket::disconnectedHandle);
}

void MyTcpSocket::readyReadHandle()
{
    QString mesg = this->readAll();
    QString userName = mesg.left(15).trimmed();
    QString targetName = mesg.mid(16,15).trimmed();
    if(targetName == "Server")
    {
        QString serverMesgType = mesg.mid(31,20).trimmed();
        if(serverMesgType == "Register")
        {
            emit registerSignal(userName, handle);
        }
    }
    else
    {
        emit forwardSignal(targetName, mesg);
    }
}

void MyTcpSocket::registerSuccessedHandle(QString userName)
{
    //Server@userNameRegisterSuccessful
    QString mesg = QString("%1@%2%3").arg("Server",15)
                                     .arg(userName, 15)
                                     .arg("RegisterSuccessful",20);
    this->write(mesg.toUtf8().data());
    this->userName = userName;
}

void MyTcpSocket::registerFailedHandle()
{
    //Server@userNameRegisterFailed
    QString mesg = QString("%1@%2%3").arg("Server",15)
                                     .arg(userName, 15)
                                     .arg("",20);
    this->write(mesg.toUtf8().data());
}

void MyTcpSocket::sendHandle(QString mesg)
{
    this->write(mesg.toUtf8().data());
}

void MyTcpSocket::sendFailedHandle(QString targetName)
{
    //Server@userNameTargetOfflineTargetName
    QString mesg = QString("%1@%2%3%4").arg("Server",15)
                                       .arg(userName, 15)
                                       .arg("TargetOffline",20)
                                       .arg(targetName);
    this->write(mesg.toUtf8().data());
}

void MyTcpSocket::disconnectedHandle()
{
    emit disconnectedSiganl(userName, handle);
    qDebug() << "disconnectedHandle";
}
