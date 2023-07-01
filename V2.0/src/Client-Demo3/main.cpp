#include "ChatMainWindow.h"
#include "SignInDialog.h"
#include "NetworkBusiness.h"
#include "RegisterDialog.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    //聊天主界面
    ChatMainWindow chatMain;
    //登录界面
    SignInDialog *signIn = new SignInDialog();
    //注册界面
    RegisterDialog *reg = new RegisterDialog();

    //登录窗口样式设定
    signIn->setWindowFlags(Qt::WindowCloseButtonHint);
    //注册窗口样式设定
    reg->setWindowFlags(Qt::WindowCloseButtonHint);

    //登录与注册窗口联动
    QObject::connect(signIn, &SignInDialog::registerSignal, reg, &RegisterDialog::registerHandle);

    //网络通讯子线程
    NetworkBusiness *network = new NetworkBusiness();
    QThread *thread = new QThread();
    network->moveToThread(thread);
    //各个界面与通讯线程联动
    //注册通讯
    QObject::connect(reg, &RegisterDialog::registerVefSignal, network, &NetworkBusiness::registerVefHandle);
    QObject::connect(reg, &RegisterDialog::registerReqSignal, network, &NetworkBusiness::registerReqHandle);
    QObject::connect(network, &NetworkBusiness::registerSucSignal, reg, &RegisterDialog::registerSucHandle);
    QObject::connect(network, &NetworkBusiness::registerFaildSignal, reg, &RegisterDialog::registerFaildHandle);
    //登录通讯
    QObject::connect(signIn, &SignInDialog::signInReqSignal, network, &NetworkBusiness::signInReqHandle);
    QObject::connect(network, &NetworkBusiness::signInSucSiganl, signIn, &SignInDialog::signInSucHandle);
    QObject::connect(network, &NetworkBusiness::signInFaildSignal, signIn, &SignInDialog::signInFaildHandle);
    //聊天通讯
    QObject::connect(network, &NetworkBusiness::signInInitSignal, &chatMain, &ChatMainWindow::signInInitHandle);
    QObject::connect(&chatMain, &ChatMainWindow::sendMesgSignal, network, &NetworkBusiness::sendMesgHandle);
    QObject::connect(network, &NetworkBusiness::displayRecMesgSiganl, &chatMain, &ChatMainWindow::displayRecMesgHandle);
    //添加好友
    QObject::connect(&chatMain, &ChatMainWindow::addFriendSignal, network, &NetworkBusiness::addFriendHandle);
    QObject::connect(network, &NetworkBusiness::newFriendSignal, &chatMain, &ChatMainWindow::newFriendHandle);
    QObject::connect(network, &NetworkBusiness::faildAddFriendSignal, &chatMain, &ChatMainWindow::faildAddFriendHandle);
    //开启子线程
    QObject::connect(network, &NetworkBusiness::start, network, &NetworkBusiness::mainBusiness);
    thread->start();
    emit network->start();
    //显示登录界面
    signIn->show();

    return a.exec();
}
