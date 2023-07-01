#include <QRandomGenerator>

#include "MyTcpSocket.h"
#include "EmailManager.h"

MyTcpSocket::MyTcpSocket(QObject *parent)
    : QTcpSocket{parent}
{
    connect(this, &MyTcpSocket::readyRead, this, &MyTcpSocket::readyReadHandle);
    connect(this, &MyTcpSocket::disconnected, this, &MyTcpSocket::disconnectedHandle);
}

void MyTcpSocket::readyReadHandle()
{
    QString mesg = this->readAll();
    QString sendAccount = mesg.left(15).trimmed();
    QString toAccount = mesg.mid(15,15).trimmed();
    QString mesgType = mesg.mid(30,20).trimmed();
    if(toAccount == "Server")
    {
        //系统消息
        QString payload = mesg.mid(50).trimmed();
        if(mesgType == "Register-Vef")
        {
            //注册验证码请求
            //生成验证码
            QString vef = QString::number(QRandomGenerator::global()->bounded(111111, 999999));
            //将验证码写入数据库
            sqlManager.setVef(payload, vef);
            //发送邮件告知
            EmailManager emailManager;
            emailManager.send(payload.toUtf8(),
                              "AirChat: Register Verification",
                              QString("Your Verification code is: %1").arg(vef));
        }
        else if(mesgType == "Register-Req")
        {
            //注册请求
            auto payloadList = payload.split('$');
            QString emailAddr = payloadList.at(0);
            QString vef = payloadList.at(1);
            if(sqlManager.checkVef(emailAddr, vef) != true)
            {
                //验证码不匹配
                QString replay = QString("%1%2%3").arg("Server", 15)
                                                  .arg("0", 15)
                                                  .arg("Register-Faild", 20);
                this->write(replay.toUtf8().data());
                return;
            }
            //验证码匹配
            if(sqlManager.checkEmail(emailAddr) == true)
            {
                //email已注册
                QString replay = QString("%1%2%3").arg("Server", 15)
                                                  .arg("0", 15)
                                                  .arg("Register-Faild", 20);
                this->write(replay.toUtf8().data());
                return;
            }
            //email未注册
            QString username = payloadList.at(2);
            QString passwd = payloadList.at(3);
            QString account = sqlManager.getNewAccount();
            sqlManager.accountInsert(emailAddr, account, passwd, username);
            QString replay = QString("%1%2%3").arg("Server", 15)
                                              .arg("0", 15)
                                              .arg("Register-Suc", 20);

            //发送邮件告知
            EmailManager emailManager;
            emailManager.send(emailAddr.toUtf8(),
                      "AirChat: Register Successful",
                      QString("Your Account number is: %1 "
                              "Your password is %2").arg(account, passwd));

            this->write(replay.toUtf8().data());
        }
        else if(mesgType == "SignIn-Req")
        {
            //登录请求
            if(sqlManager.checkAccount(sendAccount) != true)
            {
                //无此账号，登录失败
                QString replay = QString("%1%2%3").arg("Server", 15)
                                                  .arg("0", 15)
                                                  .arg("SignIn-Faild", 20);
                this->write(replay.toUtf8().data());
                return;
            }
            //登录验证
            if(sqlManager.checkSignIn(sendAccount, payload) != true)
            {
                //登录失败
                QString replay = QString("%1%2%3").arg("Server", 15)
                                                  .arg("0", 15)
                                                  .arg("SignIn-Faild", 20);
                this->write(replay.toUtf8().data());
                return;
            }
            //登录成功
            //获取初始化信息
            QString initInfo = sqlManager.getInitInfo(sendAccount);
            QString replay = QString("%1%2%3%4").arg("Server", 15)
                                                .arg("0", 15)
                                                .arg("SignIn-Init", 20)
                                                .arg(initInfo);
            account = sendAccount;
            username = initInfo.split('@').at(0);
            emit signInSucSignal(sendAccount, myHandle);
            this->write(replay.toUtf8().data());
        }
        else if(mesgType == "Friend-Add")
        {
            //添加好友请求
            if(sqlManager.checkAccount(payload) != true)
            {
                //不存在该好友
                QString replay = QString("%1%2%3").arg("Server", 15)
                                                  .arg("0", 15)
                                                  .arg("Friend-Faild", 20);
                this->write(replay.toUtf8().data());
                return;
            }
            //存在该好友
            QString friendInfo = sqlManager.addFriend(sendAccount, payload);
            QString replay = QString("%1%2%3%4").arg("Server", 15)
                                                .arg("0", 15)
                                                .arg("Friend-New", 20)
                                                .arg(friendInfo);
            this->write(replay.toUtf8().data());
            //在线同步
            replay = QString("%1%2%3%4@%5").arg("Server", 15)
                                        .arg("0", 15)
                                        .arg("Friend-New", 20)
                                        .arg(account, username);
            emit newFriendSignal(payload, replay);
        }
    }
    else
    {
        //普通消息
        emit forwardMesgProcess(toAccount, mesg);
    }
}

void MyTcpSocket::sendMesgHandle(QString mesg)
{
    this->write(mesg.toUtf8().data());
}

void MyTcpSocket::disconnectedHandle()
{
    emit disconnectedSignal(account, myHandle);
}
