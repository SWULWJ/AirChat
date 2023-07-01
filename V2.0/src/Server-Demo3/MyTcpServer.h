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

    /**
     * @brief incomingConnection
     *        重写本函数以支持多线程的TCP接入
     * @param handle
     */
    void incomingConnection(qintptr handle) override;

signals:

private slots:
    /**
     * @brief signInSucHandle
     *        登录成功处理
     * @param account
     * @param handle
     */
    void signInSucHandle(QString account, qintptr handle);

    /**
     * @brief forwardMesgHandle
     *        转发消息至相应的TCP线程,或放弃转发
     * @param toAccount
     * @param mesg
     */
    void forwardMesgHandle(QString toAccount, QString mesg);

    /**
     * @brief disconnectedHandle
     *        断连处理
     * @param account
     * @param handle
     */
    void disconnectedHandle(QString account, qintptr handle);

private:
    /**
     * @brief handleThreadHash
     *        记录TCP对应的子线程
     */
    QHash<qintptr,QThread*> handleThreadHash;

    /**
     * @brief handleChatHash
     *        记录TCP对应的业务类实例
     */
    QHash<qintptr,ChatBusiness*> handleChatHash;

    /**
     * @brief accountThreadHash
     *        记录在线账号对应的子线程
     */
    QHash<QString,QThread*> accountThreadHash;

    /**
     * @brief accountChatHash
     *        记录在线账号对应的业务实例
     */
    QHash<QString,ChatBusiness*> accountChatHash;

};

#endif // MYTCPSERVER_H
