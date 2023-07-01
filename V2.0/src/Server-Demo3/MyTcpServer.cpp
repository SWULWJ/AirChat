#include <QThread>

#include "MyTcpServer.h"
#include "ChatBusiness.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
{

}

void MyTcpServer::incomingConnection(qintptr handle)
{
    //初始化子线程转移点(业务转移点)
    ChatBusiness *chat = new ChatBusiness();
    QThread *thread = new QThread(this);
    chat->moveToThread(thread);
    handleThreadHash[handle] = thread;
    handleChatHash[handle] = chat;

    connect(chat, &ChatBusiness::start, chat, &ChatBusiness::run);
    connect(chat, &ChatBusiness::signInSucSignal, this, &MyTcpServer::signInSucHandle);
    connect(chat, &ChatBusiness::forwardMesgSignal, this, &MyTcpServer::forwardMesgHandle);
    connect(chat, &ChatBusiness::disconnectedSignal, this, &MyTcpServer::disconnectedHandle);

    //启动子线程
    qRegisterMetaType<qintptr>("qintptr");
    thread->start();
    emit chat->start(handle);
}

void MyTcpServer::signInSucHandle(QString account, qintptr handle)
{
    accountThreadHash[account] = handleThreadHash[handle];
    accountChatHash[account] = handleChatHash[handle];
    handleThreadHash.remove(handle);
    handleChatHash.remove(handle);
}

void MyTcpServer::forwardMesgHandle(QString toAccount, QString mesg)
{
    if(accountChatHash.contains(toAccount) == true)
    {
        //在线发送
        emit accountChatHash[toAccount]->sendMesgSignal(mesg);
    }
    //离线缓存
    /*      future code     */
}

void MyTcpServer::disconnectedHandle(QString account, qintptr handle)
{
    if(accountChatHash.contains(account) == true)
    {
        accountChatHash.remove(account);
        accountThreadHash[account]->quit();
        accountThreadHash[account]->wait();
    }
    else
    {
        handleChatHash.remove(handle);
        handleThreadHash[handle]->quit();
        handleThreadHash[handle]->wait();
    }
}
