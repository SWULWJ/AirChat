#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>

#include "MySQLManager.h"
#include "EmailManager.h"

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    qintptr myHandle;
    QString account;
    QString username;

public slots:
    void sendMesgHandle(QString mesg);

signals:
    /**
     * @brief signInSucSignal
     *        登录成功信号
     * @param account
     * @param handle
     */
    void signInSucSignal(QString account, qintptr handle);

    /**
     * @brief forwardMesgProcess
     *        转发请求信号
     * @param toAccount
     * @param mesg
     */
    void forwardMesgProcess(QString toAccount, QString mesg);

    /**
     * @brief disconnectedSignal
     *        TCP断连信号
     * @param account
     * @param handle
     */
    void disconnectedSignal(QString account, qintptr handle);

    /**
     * @brief newFriendSignal
     *        新好友同步信号
     * @param friendAccount
     * @param mesg
     */
    void newFriendSignal(QString friendAccount, QString mesg);

private slots:
    /**
     * @brief readyReadHandle
     *        消息到达处理
     */
    void readyReadHandle();

    /**
     * @brief disconnectedHandle
     *        断连处理
     */
    void disconnectedHandle();

private:
    MySQLManager sqlManager;

};

#endif // MYTCPSOCKET_H
