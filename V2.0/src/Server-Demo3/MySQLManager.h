#ifndef MYSQLMANAGER_H
#define MYSQLMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class MySQLManager : public QObject
{
    Q_OBJECT
public:
    explicit MySQLManager(QObject *parent = nullptr);

public:
    /**
     * @brief initDB
     *        初始化数据库连接
     */
    void initDB();

    /**
     * @brief setVefHandle
     *        添加验证码到数据库
     * @param vef
     */
    void setVef(QString emailAddr, QString vef);

    /**
     * @brief checkVef
     *        验证验证码有效性
     * @param emailAddr
     * @param vef
     * @return bool 验证码是否匹配
     */
    bool checkVef(QString emailAddr, QString vef);

    /**
     * @brief checkAccount
     *        验证是否存在目标账号
     * @param account
     * @return bool 账号是否存在
     */
    bool checkAccount(QString account);

    /**
     * @brief checkEmail
     *        验证邮箱是否已注册
     * @param emailAddr
     * @return bool 邮箱是否已注册
     */
    bool checkEmail(QString emailAddr);

    /**
     * @brief accountInsert
     *        注册账户
     * @param emailAddr 待注册邮箱
     * @param account   账号
     * @param passwd    密码
     * @param username  用户名
     */
    void accountInsert(QString emailAddr, QString account, QString passwd, QString username);

    /**
     * @brief getNewAccount
     *        获取新的合法账号
     * @return  账号
     */
    QString getNewAccount();

    /**
     * @brief checkSignIn
     *        登录验证
     * @param account   账号
     * @param passwd    密码
     * @return bool 验证结果
     */
    bool checkSignIn(QString account, QString passwd);

    /**
     * @brief getInitInfo
     *        获取登录初始化信息
     * @param account
     * @return
     */
    QString getInitInfo(QString account);

    /**
     * @brief addFriend
     *        添加好友
     * @param account
     * @param friendAccount
     * @return 返回好友信息
     */
    QString addFriend(QString account, QString friendAccount);

signals:

private:
    QSqlDatabase sqlDB;
    static int id;

};

#endif // MYSQLMANAGER_H
