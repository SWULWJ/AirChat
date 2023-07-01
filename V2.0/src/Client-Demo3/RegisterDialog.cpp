#include <QRegExpValidator>
#include <QMessageBox>
#include <QTimer>

#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"

#pragma execution_character_set("utf-8")

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(&vefTimer, &QTimer::timeout, this, &RegisterDialog::vefTimeoutHandle);
    connect(&reqTimer, &QTimer::timeout, this, &RegisterDialog::reqTimeoutHandle);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::registerHandle()
{
    show();
}

void RegisterDialog::registerSucHandle()
{
    reqTimer.stop();
    ui->ButtonRegister->setDisabled(false);
    QMessageBox::information (this,
                         "Success",
                         QString("注册成功！"),
                         QMessageBox::Ok);
    hide();
}

void RegisterDialog::registerFaildHandle()
{
    reqTimer.stop();
    ui->ButtonRegister->setDisabled(false);
    QMessageBox::warning(this,
                         "Warning",
                         QString("注册失败！\n"
                                 "邮箱已注册或验证码错误"
                                 "\n忘记密码请联系管理员"),
                         QMessageBox::Ok);
}

void RegisterDialog::on_ButtonRegister_clicked()
{
    QString email = ui->EditEmail->text();
    QRegExp emailRegExp("[a-zA-Z0-9-_]+@[a-zA-Z0-9-_]+\\.[a-zA-Z]+");
    //邮箱格式有误
    if(emailRegExp.exactMatch(email) != true)
    {
        QMessageBox::warning(this,
                             "Warning",
                             QString("邮箱格式错误"),
                             QMessageBox::Ok);
        return;
    }
    QString vef = ui->EditVerify->text();
    if(vef == "")
    {
        QMessageBox::warning(this,
                             "Warning",
                             QString("验证码不为空"),
                             QMessageBox::Ok);
        return;
    }
    QString passwd = ui->EditPasswd->text();
    QRegExp passwdRegExp("^[a-zA-Z]\\w{5,14}$");
    if(passwdRegExp.exactMatch(passwd) != true)
    {
        QMessageBox::warning(this,
                             "Warning",
                             QString("密码需要以字母开头\n"
                                     "长度在6~15之间\n"
                                     "只能包含字母、数字和下划线"),
                             QMessageBox::Ok);
        return;
    }
    QString username = ui->EditUsername->text();
    if(username == "")
    {
        QMessageBox::warning(this,
                             "Warning",
                             QString("用户名不为空"),
                             QMessageBox::Ok);
        return;
    }

    //请求注册
    emit registerReqSignal(email, vef, username, passwd);
    reqTimer.start(15000);
    ui->ButtonRegister->setDisabled(true);
}


void RegisterDialog::on_ButtonVerify_clicked()
{
    QString email = ui->EditEmail->text();
    QRegExp emailRegExp("[a-zA-Z0-9-_]+@[a-zA-Z0-9-_]+\\.[a-zA-Z]+");
    //邮箱格式有误
    if(emailRegExp.exactMatch(email) != true)
    {
        QMessageBox::warning(this,
                             "Warning",
                             QString("邮箱格式错误"),
                             QMessageBox::Ok);
        return;
    }
    //请求验证码
    emit registerVefSignal(email);
    ui->ButtonVerify->setDisabled(true);
    //30s
    vefTimer.start(30000);
}

void RegisterDialog::vefTimeoutHandle()
{
    ui->ButtonVerify->setDisabled(false);
    vefTimer.stop();
}

void RegisterDialog::reqTimeoutHandle()
{
    reqTimer.stop();
    ui->ButtonRegister->setDisabled(false);
    QMessageBox::warning(this,
                         "Warning",
                         QString("网络问题！\n注册可能超时"),
                         QMessageBox::Ok);
}
