#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "MySQLManager.h"

int MySQLManager::id = 1;

MySQLManager::MySQLManager(QObject *parent)
    : QObject{parent}
{
    sqlDB = QSqlDatabase::addDatabase("QMYSQL", QString::number(++id));
    sqlDB.setHostName("127.0.0.1");//部署
//    sqlDB.setHostName("192.168.87.131");//调试
    sqlDB.setUserName("admin");
    sqlDB.setPassword("AirChat@db");//部署
//    sqlDB.setPassword("MySQL&db12");//调试
    sqlDB.setDatabaseName("airchat");
    sqlDB.setConnectOptions("SSL_KEY=C:\\ProgramData\\MySQL\\MySQL Server 8.0\\Data\\client-key.pem;"
                          "SSL_CERT=C:\\ProgramData\\MySQL\\MySQL Server 8.0\\Data\\client-cert.pem;"
                          "SSL_CA=C:\\ProgramData\\MySQL\\MySQL Server 8.0\\Data\\ca.pem;"
                          "CLIENT_IGNORE_SPACE=1");
    sqlDB.open();
}

void MySQLManager::setVef(QString emailAddr, QString vef)
{
    QString sql = QString("Select * from email_verify "
                           "Where email='%1'").arg(emailAddr);
    QSqlQuery query("", sqlDB);
    query.exec(sql);
    query.first();
    if(query.size() == 1)
    {
        //已存在验证码
        sql = QString("Update email_verify "
                              "Set verify='%1' "
                              "Where email='%2'").arg(vef,emailAddr);
    }
    else
    {
        //不存在验证码
        sql = QString("Insert into email_verify(email,verify) "
                              "values('%1','%2')").arg(emailAddr, vef);
    }
    query.exec(sql);
}

bool MySQLManager::checkVef(QString emailAddr, QString vef)
{
    QString sql = QString("Select verify from email_verify "
                            "Where email='%1'").arg(emailAddr);
    QSqlQuery query("", sqlDB);
    query.exec(sql);
    query.first();
    if(vef != query.value(0).toString())
    {
        //验证码不匹配
        return false;
    }
    //验证码匹配,移除该条记录
    sql = QString("Delete from email_verify "
                  "Where email='%1'").arg(emailAddr);
    query.exec(sql);
    return true;
}

bool MySQLManager::checkAccount(QString account)
{
    QString sql = QString("Select * from user_account "
                          "Where account='%1'").arg(account);
    QSqlQuery query("", sqlDB);
    query.exec(sql);
    if(query.size() == 1)
    {
        return true;
    }
    return false;
}

bool MySQLManager::checkEmail(QString emailAddr)
{
    QString sql = QString("Select * from user_account "
                          "Where email='%1'").arg(emailAddr);
    QSqlQuery query("", sqlDB);
    query.exec(sql);
    if(query.size() == 1)
    {
        return true;
    }
    return false;
}

void MySQLManager::accountInsert(QString emailAddr, QString account, QString passwd, QString username)
{
    QString sql = QString("Insert into user_account(email,account,passwd,username) "
                          "values('%1','%2','%3','%4')")
                            .arg(emailAddr, account, passwd, username);
    QSqlQuery query("", sqlDB);
    query.exec(sql);
}

QString MySQLManager::getNewAccount()
{
    QString sql = QString("Select Max(id) "
                          "From user_account");
    QSqlQuery query("", sqlDB);
    query.exec(sql);
    query.first();
    int id = query.value(0).toInt();

    sql = QString("Select account "
                  "From user_account "
                  "Where id=%1").arg(id);
    query.exec(sql);
    query.first();
    int account = query.value(0).toInt();

    return QString::number(++account);
}

bool MySQLManager::checkSignIn(QString account, QString passwd)
{

    QString sql = QString("Select passwd "
                          "From user_account "
                          "Where account='%1'").arg(account);
    QSqlQuery query("", sqlDB);
    query.exec(sql);
    query.first();
    if(query.value(0).toString() == passwd)
    {
        return true;
    }
    return false;
}

QString MySQLManager::getInitInfo(QString account)
{
    //获取登录账户信息
    QString sql = QString("Select username "
                          "From user_account "
                          "Where account='%1'").arg(account);
    QSqlQuery query("", sqlDB);
    query.exec(sql);
    query.first();
    QString username = query.value(0).toString();

    //获取好友信息
    sql = QString("Select friend "
                  "From friend_table "
                  "Where account='%1'").arg(account);
    query.exec(sql);

    QSqlDatabase friendDB = QSqlDatabase::addDatabase("QMYSQL", QString::number(++id));
    friendDB.setHostName("127.0.0.1");//部署
//    sqlDB.setHostName("192.168.87.131");//调试
    friendDB.setUserName("admin");
    friendDB.setPassword("AirChat@db");//部署
//    sqlDB.setPassword("MySQL&db12");//调试
    friendDB.setDatabaseName("airchat");
    friendDB.setConnectOptions("SSL_KEY=C:\\ProgramData\\MySQL\\MySQL Server 8.0\\Data\\client-key.pem;"
                               "SSL_CERT=C:\\ProgramData\\MySQL\\MySQL Server 8.0\\Data\\client-cert.pem;"
                               "SSL_CA=C:\\ProgramData\\MySQL\\MySQL Server 8.0\\Data\\ca.pem;"
                               "CLIENT_IGNORE_SPACE=1");
    friendDB.open();

    QSqlQuery queryFriend("", friendDB);
    QByteArray friendInfo;
    QString friendAccount;
    QString friendName;
    while(query.next())
    {
        friendAccount = query.value(0).toString();
        sql = QString("Select username "
                      "From user_account "
                      "Where account='%1'").arg(friendAccount);
        queryFriend.exec(sql);
        queryFriend.first();
        friendName = queryFriend.value(0).toString();
        friendInfo.append(QString("%1@%2#").arg(friendName,friendAccount).toUtf8());
    }
    return QString("%1@%2>:%3").arg(username, account, friendInfo);
    friendDB.close();
}

QString MySQLManager::addFriend(QString account, QString friendAccount)
{
    QString sql = QString("Insert into friend_table(account,friend) "
                          "values('%1','%2')").arg(account, friendAccount);
    QSqlQuery query("", sqlDB);
    query.exec(sql);

    sql = QString("Insert into friend_table(account,friend) "
                  "values('%1','%2')").arg(friendAccount, account);
    query.exec(sql);

    sql = QString("Select username "
                  "From user_account "
                  "Where account='%1'").arg(friendAccount);
    query.exec(sql);
    query.first();

    return QString("%1@%2").arg(query.value(0).toString(), friendAccount);
}
