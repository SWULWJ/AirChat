#include <QMouseEvent>
#include <QMessageBox>

#include "SignInDialog.h"
#include "ui_SignInDialog.h"
#include "RegisterDialog.h"

#pragma execution_character_set("utf-8")

SignInDialog::SignInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInDialog)
{
    ui->setupUi(this);
    ui->labelRegister->installEventFilter(this);
    connect(&timer, &QTimer::timeout, this, &SignInDialog::timeoutHandle);
}

bool SignInDialog::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->labelRegister)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = (QMouseEvent*)event;
            if(mouseEvent->button() == Qt::LeftButton)
            {
                RegisterDialog registerDialog;
                emit registerSignal();
                return true;
            }
        }
        return false;
    }
    return QDialog::eventFilter(obj, event);
}

SignInDialog::~SignInDialog()
{
    delete ui;
}

void SignInDialog::on_ButtonSignIn_clicked()
{
    QString account = ui->EditAccount->text();
    if(account == "")
    {
        QMessageBox::warning(this,
                             "Warning",
                             QString("账号不能为空"),
                             QMessageBox::Ok);
        return;
    }
    QString passwd = ui->EditPasswd->text();
    if(passwd == "")
    {
        QMessageBox::warning(this,
                             "Warning",
                             QString("密码不能为空"),
                             QMessageBox::Ok);
        return;
    }
    emit signInReqSignal(account, passwd);
    ui->ButtonSignIn->setDisabled(true);
    timer.start(5000);
}

void SignInDialog::timeoutHandle()
{
    timer.stop();
    ui->ButtonSignIn->setDisabled(false);
    QMessageBox::warning(this,
                         "Warning",
                         QString("网络问题！\n登录可能超时"),
                         QMessageBox::Ok);
}

void SignInDialog::signInSucHandle()
{
    timer.stop();
    ui->ButtonSignIn->setDisabled(false);
    hide();
}

void SignInDialog::signInFaildHandle()
{
    timer.stop();
    ui->ButtonSignIn->setDisabled(false);
    QMessageBox::warning(this,
                         "Warning",
                         QString("账号或密码错误"),
                         QMessageBox::Ok);
}
