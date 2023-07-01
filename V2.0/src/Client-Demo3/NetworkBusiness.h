#ifndef NETWORKBUSINESS_H
#define NETWORKBUSINESS_H

#include <QObject>
#include <QHostAddress>
#include <QTimer>

/**
 * @brief The NetworkBusiness class
 *        网络通讯处理类
 */
class NetworkBusiness : public QObject
{
    Q_OBJECT
public:
    explicit NetworkBusiness(QObject *parent = nullptr);

public slots:
    /**
     * @brief signInReqHandle
     *        生成登录窗口的登录请求报文
     * @param account   账号
     * @param passwd    密码
     */
    void signInReqHandle(QString account, QString passwd);

    /**
     * @brief registerVefHandle
     *        生成请求验证码报文
     * @param email     邮箱地址
     */
    void registerVefHandle(QString email);

    /**
     * @brief registerReqHandle
     *        生成请求注册(确认验证码并设置密码)报文
     * @param email     邮箱地址
     * @param vef       验证码
     * @param username  用户名
     * @param passwd    设置的密码
     */
    void registerReqHandle(QString email, QString vef, QString username, QString passwd);


    /**
     * @brief addFriendHandle
     *        生成添加好友请求报文
     * @param account
     * @param friendAccount
     */
    void addFriendHandle(QString account, QString friendAccount);

    /**
     * @brief newMesgHandle
     *        处理收到的消息
     * @param mesg
     */
    void newMesgHandle(QString mesg);

    /**
     * @brief sendMesgHandle
     *        处理将发送消息
     * @param targetAccount
     * @param payload
     */
    void sendMesgHandle(QString account, QString targetAccount, QString payload);


public:
    /**
     * @brief mainBusiness
     *        子线程启动初始
     */
    void mainBusiness();

signals:
    /**
     * @brief start
     *        子线程启动信号
     */
    void start();

    /**
     * @brief registerSucSignal
     *        注册成功信号
     */
    void registerSucSignal();

    /**
     * @brief registerFaildSignal
     *        注册失败信号
     */
    void registerFaildSignal();

    /**
     * @brief signInSucInitSiganl
     *        登录成功信号
     */
    void signInSucSiganl();

    /**
     * @brief signInInitSignal
     *        登录初始化信号
     * @param mesg
     */
    void signInInitSignal(QString mesg);

    /**
     * @brief signInFaildSignal
     *        登录失败信号
     */
    void signInFaildSignal();

    /**
     * @brief newFriendSignal
     *        增加新好友信号
     * @param friendAccountInfo
     */
    void newFriendSignal(QString friendAccountInfo);

    /**
     * @brief faildAddFriendSignal
     *        添加新好友失败信号
     * @param friendAccount
     */
    void faildAddFriendSignal(QString friendAccount);

    /**
     * @brief submitMesgSiganl
     *        提交待传输消息
     * @param mesg
     */
    void submitMesgSiganl(char* mesg);

    /**
     * @brief displayRecMesgSiganl
     *        展示信息信号
     * @param targetAccount     来信用户
     * @param payload           具体信息
     */
    void displayRecMesgSiganl(QString targetAccount, QString payload);
};

#endif // NETWORKBUSINESS_H
