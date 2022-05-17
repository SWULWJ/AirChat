#ifndef CHATBUSINESS_H
#define CHATBUSINESS_H

#include <QObject>

class ChatBusiness : public QObject
{
    Q_OBJECT
public:
    explicit ChatBusiness(QObject *parent = nullptr);

    void mainBusiness(qintptr handle);

protected slots:
    void socketRegisterHandle(QString userName, qintptr handle);
    void socketForwardHandle(QString targetName, QString mesg);
    void disconnectedHandle(QString userName, qintptr handle);

signals:
    void registerSiganl(QString userName, qintptr handle);
    void forwardSiganl(QString targetName, QString mesg);
    void sendSiganl(QString mesg);
    void removeAndClose(QString userName, qintptr handle);

    void registerSuccessedSiganl(QString userName);
    void registerFailedSiganl();
    void sendFailedSiganl(QString targetName);

    void start(qintptr handle);
};

#endif // CHATBUSINESS_H
