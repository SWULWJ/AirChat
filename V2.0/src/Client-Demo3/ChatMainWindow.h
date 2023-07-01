#ifndef CHATMAINWINDOW_H
#define CHATMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ChatMainWindow; }
QT_END_NAMESPACE

/**
 * @brief The ChatMainWindow class
 *        聊天主界面类
 */
class ChatMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ChatMainWindow(QWidget *parent = nullptr);
    ~ChatMainWindow();

signals:
    /**
     * @brief addFriendSignal
     *        提交添加好友请求
     * @param account
     * @param friendAccount
     */
    void addFriendSignal(QString account, QString friendAccount);

    /**
     * @brief sendMesgSignal
     *        提交消息发送请求
     * @param account
     * @param targetAccount
     * @param payload
     */
    void sendMesgSignal(QString account, QString targetAccount, QString payload);

public slots:
    /**
     * @brief signInInitHandle
     *        根据用户数据初始化
     * @param mesg  用户数据(好友列表)
     */
    void signInInitHandle(QString mesg);

    /**
     * @brief displayRecMesgHandle
     *        处理收到的信息，转到响应的widget
     * @param targetAccount     来信人
     * @param payload           信息
     */
    void displayRecMesgHandle(QString targetAccount, QString payload);

    /**
     * @brief newFriendHandle
     *        处理新增好友信号，添加到列表
     * @param friendAccountInfo
     */
    void newFriendHandle(QString friendAccountInfo);

    /**
     * @brief faildAddFriendHandle
     *        添加好友失败响应
     * @param friendAccount
     */
    void faildAddFriendHandle(QString friendAccount);

private slots:

    /**
     * @brief aboutAirChat
     *        actionAirChat响应
     */
    void aboutAirChat();

    /**
     * @brief on_ButtonAddFriend_clicked
     *        添加好友控件响应
     */
    void on_ButtonAddFriend_clicked();

    /**
     * @brief addFriendHandle
     *        处理控件的添加好友消息请求
     * @param account   好友账号
     */
    void addFriendHandle(QString friendAccount);

    /**
     * @brief on_listWidgetFriend_currentRowChanged
     *        聊天界面切换
     * @param currentRow
     */
    void on_listWidgetFriend_currentRowChanged(int currentRow);

    /**
     * @brief sendMesgHandle
     *        处理发送控件的发送请求
     * @param targetAccount
     * @param payload
     */
    void sendMesgHandle(QString targetAccount, QString payload);

private:
    Ui::ChatMainWindow *ui;
    QString username;
    QString account;
    QHash<QString, QString> usernameTable;  //Friend-account hash表,查找对应聊天widget

    /**
     * @brief addListAndStackedWidget
     *        更新好友列表和聊天界面
     * @param friendName
     * @param friendAccount
     */
    void addListAndStackedWidget(QString friendName, QString friendAccount);
};
#endif // CHATMAINWINDOW_H
