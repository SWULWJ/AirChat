#ifndef EMAILMANAGER_H
#define EMAILMANAGER_H

#include<QByteArray>
#include<QString>
#include<QTcpSocket>

#define EMAIL_USERNAME ("AirChat@163.com")
#define EMAIL_PASSWD ("OAWACNGVPYNPQCKA")

class EmailManager
{
public:
    EmailManager(QByteArray username = EMAIL_USERNAME, QByteArray password = EMAIL_PASSWD);
    ~EmailManager();
    void send(QByteArray recvaddr,QString subject,QString content);
private:
    QTcpSocket * clientsocket;
    QByteArray username;
    QByteArray password;
    QByteArray recvaddr;
    QByteArray mailfrom = "mail from:<";
    QByteArray rcptto = "rcpt to:<";
    QByteArray prefrom = "from:";
    QByteArray preto = "to:";
    QByteArray presubject ="subject:";
    QString subject;                //主题
    QString content;                //发送内容
    QByteArray recvdata;            //接收到的数据
};
#endif // EMAILMANAGER_H
