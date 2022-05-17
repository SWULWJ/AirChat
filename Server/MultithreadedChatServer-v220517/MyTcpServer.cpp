#include <QThread>

#include "MyTcpServer.h"
#include "ChatBusiness.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
{

}

void MyTcpServer::incomingConnection(qintptr handle)
{
    QThread *thread = new QThread(this);
    ChatBusiness *chatBusiness = new ChatBusiness();
    chatBusiness->moveToThread(thread);
    socketThreadHash[handle] = thread;
    threadChatHash[thread] = chatBusiness;
    connect(chatBusiness, &ChatBusiness::registerSiganl, this, &MyTcpServer::registerHandle);
    connect(chatBusiness, &ChatBusiness::forwardSiganl, this, &MyTcpServer::forwardHandle);
    connect(chatBusiness, &ChatBusiness::start, chatBusiness, &ChatBusiness::mainBusiness);
    connect(chatBusiness, &ChatBusiness::removeAndClose, this, &MyTcpServer::closeThreadHandle);
    qRegisterMetaType<qintptr>("qintptr");
    thread->start();
    emit chatBusiness->start(handle);
}

void MyTcpServer::registerHandle(QString userName, qintptr handle)
{
    if(userThreadHash.contains(userName) == true)
    {
        emit threadChatHash[socketThreadHash[handle]]->registerFailedSiganl();
    }
    else
    {
        userThreadHash[userName] = socketThreadHash[handle];
        socketThreadHash.remove(handle);
        emit threadChatHash[userThreadHash[userName]]->registerSuccessedSiganl(userName);
    }
}

void MyTcpServer::forwardHandle(QString targetName, QString mesg)
{
    if(userThreadHash.contains(targetName) == true)
    {
        emit threadChatHash[userThreadHash[targetName]]->sendSiganl(mesg);
    }
    else
    {
        QString userName = mesg.left(15).trimmed();
        qDebug() << userName;
        qDebug() << userThreadHash[userName];
        emit threadChatHash[userThreadHash[userName]]->sendFailedSiganl(targetName);
    }
}

void MyTcpServer::closeThreadHandle(QString userName, qintptr handle)
{
    if(userThreadHash.contains(userName) == true)
    {
        userThreadHash[userName]->quit();
        userThreadHash[userName]->wait();
        userThreadHash.remove(userName);
    }
    else
    {
        socketThreadHash[handle]->quit();
        socketThreadHash[handle]->wait();
        socketThreadHash.remove(handle);
    }
}
