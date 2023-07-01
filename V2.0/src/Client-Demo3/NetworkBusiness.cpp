#include "NetworkBusiness.h"
#include "MyTcpSocket.h"

#define SERVER_IP ("139.9.234.113")
#define SERVER_PORT (8848)

NetworkBusiness::NetworkBusiness(QObject *parent)
    : QObject{parent}
{

}

void NetworkBusiness::mainBusiness()
{
    MyTcpSocket *tcpSocket = new MyTcpSocket(this);
    connect(this, &NetworkBusiness::submitMesgSiganl, tcpSocket, &MyTcpSocket::sendHandle);
    connect(tcpSocket, &MyTcpSocket::newMesg, this, &NetworkBusiness::newMesgHandle);
    tcpSocket->init(SERVER_IP, SERVER_PORT);
}

void NetworkBusiness::newMesgHandle(QString mesg)
{
    QString sendUser = mesg.left(15).trimmed();
    QString mesgType = mesg.mid(30,20).trimmed();
    QString payload = mesg.mid(50);
    if(sendUser == "Server")
    {
        //服务器系统消息
        if(mesgType == "Register-Suc")
        {
            //注册成功
            emit registerSucSignal();
        }
        else if(mesgType == "Register-Faild")
        {
            //注册失败
            emit registerFaildSignal();
        }
        else if(mesgType == "SignIn-Init")
        {
            //登录成功，开始初始化
            emit signInSucSiganl();
            emit signInInitSignal(payload);
        }
        else if(mesgType == "SignIn-Faild")
        {
            //登录失败
            emit signInFaildSignal();
        }
        else if(mesgType == "Friend-New")
        {
            //添加好友成功或新增好友
            emit newFriendSignal(payload);
        }
        else if(mesgType == "Friend-Faild")
        {
            //添加好友成功或新增好友
            emit faildAddFriendSignal(payload);
        }
    }
    else
    {
        //普通消息
        emit displayRecMesgSiganl(sendUser, payload);
    }
}

void NetworkBusiness::signInReqHandle(QString account, QString passwd)
{
    QString mesg = QString("%1%2%3%4").arg(account, 15)
                                      .arg("Server", 15)
                                      .arg("SignIn-Req", 20)
                                      .arg(passwd);
    emit submitMesgSiganl(mesg.toUtf8().data());
}

void NetworkBusiness::registerVefHandle(QString email)
{
    QString mesg = QString("%1%2%3%4").arg(0, 15)
                                      .arg("Server", 15)
                                      .arg("Register-Vef", 20)
                                      .arg(email);
    emit submitMesgSiganl(mesg.toUtf8().data());
}

void NetworkBusiness::registerReqHandle(QString email, QString vef, QString username, QString passwd)
{
    QString mesg = QString("%1%2%3%4$%5$%6$%7").arg(0, 15)
                                               .arg("Server", 15)
                                               .arg("Register-Req", 20)
                                               .arg(email,vef,username,passwd);
    emit submitMesgSiganl(mesg.toUtf8().data());
}

void NetworkBusiness::addFriendHandle(QString account, QString friendAccount)
{
    QString mesg = QString("%1%2%3%4").arg(account, 15)
                                      .arg("Server", 15)
                                      .arg("Friend-Add", 20)
                                      .arg(friendAccount);
    emit submitMesgSiganl(mesg.toUtf8().data());
}

void NetworkBusiness::sendMesgHandle(QString account, QString targetAccount, QString payload)
{
    QString mesg = QString("%1%2%3%4").arg(account, 15)
                                      .arg(targetAccount, 15)
                                      .arg("Mesg", 20)
                                      .arg(payload);
    emit submitMesgSiganl(mesg.toUtf8().data());
}
