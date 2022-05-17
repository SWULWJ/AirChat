#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>

#include "ChatBusiness.h"

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);

    void incomingConnection(qintptr handle) override;

protected:
    QHash<qintptr, QThread*> socketThreadHash;
    QHash<QString, QThread*> userThreadHash;
    QHash<QThread*, ChatBusiness*> threadChatHash;

protected slots:
    void registerHandle(QString userName, qintptr handle);
    void forwardHandle(QString targetName, QString mesg);
    void closeThreadHandle(QString userName, qintptr handle);

signals:

};

#endif // MYTCPSERVER_H
