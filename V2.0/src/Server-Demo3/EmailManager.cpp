#include "EmailManager.h"

EmailManager::EmailManager(QByteArray username,QByteArray password) :
    username(username), password(password)
{

}

void EmailManager::send(QByteArray recvaddr,QString subject,QString content)
{
    this->recvaddr = recvaddr;
    this->subject = subject;
    this->content = content;
    QByteArray usernametmp = this->username;
    QByteArray recvaddrtmp = this->recvaddr;

    clientsocket=new QTcpSocket();
    clientsocket->connectToHost("smtp.163.com",25,QTcpSocket::ReadWrite);
    //防止粘包并等待163响应
    clientsocket->waitForConnected(1000);
    clientsocket->waitForReadyRead(1000);

    clientsocket->write("HELO EmailManager.163.com\r\n");
    clientsocket->waitForReadyRead(1000);

    clientsocket->write("AUTH LOGIN\r\n");
    clientsocket->waitForReadyRead(1000);

    clientsocket->write(username.toBase64().append("\r\n"));
    clientsocket->waitForReadyRead(1000);

    clientsocket->write(password.toBase64().append("\r\n"));
    clientsocket->waitForReadyRead(1000);

    clientsocket->write(mailfrom.append(usernametmp.append(">\r\n")));
    clientsocket->waitForReadyRead(1000);

    clientsocket->write(rcptto.append(recvaddrtmp.append(">\r\n")));
    clientsocket->waitForReadyRead(1000);

    clientsocket->write("data\r\n");
    clientsocket->waitForReadyRead(1000);

    usernametmp = this->username;
    recvaddrtmp = this->recvaddr;

    clientsocket->write(prefrom.append(usernametmp.append("\r\n")));
    clientsocket->write(preto.append(recvaddrtmp.append("\r\n")));
    clientsocket->write(presubject.append(subject.toUtf8().append("\r\n")));
    clientsocket->write("\r\n");
    clientsocket->write(content.toUtf8().append("\r\n"));
    clientsocket->write(".\r\n");
    clientsocket->waitForReadyRead(1000);

    clientsocket->write("quit\r\n");
    clientsocket->waitForReadyRead(1000);
}

EmailManager::~EmailManager()
{
    delete clientsocket;
}

