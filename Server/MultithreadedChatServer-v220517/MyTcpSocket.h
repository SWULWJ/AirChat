#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr, qintptr handle = NULL);

protected:
    qintptr handle;
    QString userName;

protected slots:
//    void connectedHandle();
    void readyReadHandle();
    void disconnectedHandle();

public slots:
    void registerSuccessedHandle(QString userName);
    void registerFailedHandle();
    void sendHandle(QString mesg);
    void sendFailedHandle(QString targetName);

signals:
    void registerSignal(QString userName, qintptr handle);
    void forwardSignal(QString targetName, QString mesg);
    void disconnectedSiganl(QString userName, qintptr handle);

};

#endif // MYTCPSOCKET_H
