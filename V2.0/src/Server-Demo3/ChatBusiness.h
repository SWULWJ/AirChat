#ifndef CHATBUSINESS_H
#define CHATBUSINESS_H

#include <QObject>

#include "MyTcpSocket.h"

class ChatBusiness : public QObject
{
    Q_OBJECT
public:
    explicit ChatBusiness(QObject *parent = nullptr);

    /**
     * @brief run
     *        子线程启动入口
     * @param handle
     */
    void run(qintptr handle);

public slots:
    /**
     * @brief disconnectedHandle
     *        断连处理
     * @param account
     * @param handle
     */
    void disconnectedHandle(QString account, qintptr handle);

signals:
    /**
     * @brief start
     *        子线程启动信号
     * @param handle
     */
    void start(qintptr handle);

    /**
     * @brief signInSucSignal
     *        登录成功信号
     * @param account
     * @param handle
     */
    void signInSucSignal(QString account, qintptr handle);

    /**
     * @brief forwardMesgSignal
     *        消息转发信号
     * @param toAccount
     * @param mesg
     */
    void forwardMesgSignal(QString toAccount, QString mesg);

    /**
     * @brief sendMesgSignal
     *        发送消息信号
     * @param mesg
     */
    void sendMesgSignal(QString mesg);

    /**
     * @brief disconnectedSignal
     *        断连处理
     * @param account
     * @param handle
     */
    void disconnectedSignal(QString account, qintptr handle);

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
     *        消息转发处理
     * @param toAccount
     * @param mesg
     */
    void forwardMesgHandle(QString toAccount, QString mesg);
};

#endif // CHATBUSINESS_H
