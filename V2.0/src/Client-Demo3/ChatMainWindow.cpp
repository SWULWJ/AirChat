#include "ChatMainWindow.h"
#include "ui_ChatMainWindow.h"
#include "AddFriendDialog.h"
#include "ChatWidget.h"

#include <QTextBrowser>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

ChatMainWindow::ChatMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatMainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAirChat, &QAction::triggered, this, &ChatMainWindow::aboutAirChat);
}

ChatMainWindow::~ChatMainWindow()
{
    delete ui;
}

void ChatMainWindow::signInInitHandle(QString mesg)
{
    //登录成功，显示窗口
    show();
    //更具服务器初始化数据，初始化界面
    //username@account>:Friendname@account#Friendname@account#...
    //初始化个人信息
    auto mesgSplitList = mesg.split(">:");
    QString user = mesgSplitList.at(0);
    this->username = user.split("@").at(0);
    this->account = user.split('@').at(1);
    this->setWindowTitle(QString("AirChat-%1").arg(username));
    //初始化好友消息界面
    if(mesgSplitList.at(1) == "")
    {
        return;
    }
    QString friends = mesgSplitList.at(1);
    auto friendList = friends.split('#');
    foreach(auto itm, friendList)
    {
        //初始化好友列表
        if(itm == "")
        {
            continue;
        }
        QString friendName = itm.split('@').at(0);
        QString friendAccount = itm.split('@').at(1);
        addListAndStackedWidget(friendName, friendAccount);
    }
}

void ChatMainWindow::aboutAirChat()
{
    QMessageBox::information(this,
                         "AirChat",
                         QString("开发人员：李汪骏\n"
                                 "专业年级：19级软件工程4班\n"
                                 "学号：222019321062112\n"
                                 "产品名称：AirChat-即时聊天软件\n"
                                 "Copyright ©2022 李汪骏, All Rights Reserved"),
                         QMessageBox::Ok);
}

void ChatMainWindow::on_ButtonAddFriend_clicked()
{
    //初始化添加好友窗口
    AddFriendDialog addFriend;
    addFriend.setWindowFlags(Qt::WindowCloseButtonHint);
    addFriend.setWindowTitle("AddFriend");
    //添加信号槽
    connect(&addFriend, &AddFriendDialog::addFriendSignal, this, &ChatMainWindow::addFriendHandle);
    addFriend.show();
    //启用事件循环
    addFriend.exec();
}

void ChatMainWindow::addFriendHandle(QString friendAccount)
{
    if(usernameTable.contains(friendAccount) == true)
    {
        QMessageBox::warning(this,
                             "warning",
                             QString("目标账号：%1\n已经是好友").arg(friendAccount),
                             QMessageBox::Ok);
        return;
    }
    emit addFriendSignal(account, friendAccount);
}


void ChatMainWindow::on_listWidgetFriend_currentRowChanged(int currentRow)
{
    ui->stackedWidget->setCurrentIndex(currentRow);
}

void ChatMainWindow::sendMesgHandle(QString targetAccount, QString payload)
{
    emit sendMesgSignal(account, targetAccount, payload);
}

void ChatMainWindow::displayRecMesgHandle(QString targetAccount, QString payload)
{
    QString accountName = usernameTable[targetAccount];
    QString objName = QString("%1(%2)").arg(accountName, targetAccount);
    auto targetWidget = ui->stackedWidget->findChild<QWidget*>(objName);
    ((ChatWidget *)targetWidget)->displayRecMesg(payload);
}

void ChatMainWindow::newFriendHandle(QString friendAccountInfo)
{
    QString friendName = friendAccountInfo.split('@').at(0);
    QString friendAccount = friendAccountInfo.split('@').at(1);
    addListAndStackedWidget(friendName, friendAccount);
}

void ChatMainWindow::faildAddFriendHandle(QString friendAccount)
{
    QMessageBox::warning(this,
                         "Warning",
                         QString("好友添加失败！\n目标账号不存在！"),
                         QMessageBox::Ok);
}

void ChatMainWindow::addListAndStackedWidget(QString friendName, QString friendAccount)
{
    QString objName = QString("%1(%2)").arg(friendName, friendAccount);
    ui->listWidgetFriend->addItem(objName);
    //加入hash表
    usernameTable[friendAccount] = friendName;
    //创建对应的聊天界面
    ChatWidget *chatWidget = new ChatWidget(this);
    //设置对应的对象名
    chatWidget->setObjectName(objName);
    //初始化界面标签
    auto labelFriendName = chatWidget->findChild<QLabel*>("labelFriendName");
    labelFriendName->setText(objName);
    //初始化信号槽
    connect(chatWidget, &ChatWidget::sendMesgSignal, this, &ChatMainWindow::sendMesgHandle);
    //将聊天界面加入分页管理
    ui->stackedWidget->addWidget(chatWidget);
}
