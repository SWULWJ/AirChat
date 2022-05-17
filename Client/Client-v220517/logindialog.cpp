#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::connectedFailedhandle()
{
    QMessageBox::warning(this,
                         "Warning",
                         "The connection timed out",
                         QMessageBox::Ok);
    ui->LoginButton->setDisabled(false);
    ui->statusLabel->clear();
}

void LoginDialog::registerSucccessedHandle()
{
    hide();
    ui->LoginButton->setDisabled(false);
    ui->statusLabel->clear();
}

void LoginDialog::registerFailedHandle()
{
    QMessageBox::warning(this,
                         "Warning",
                         "The Nickname is already in use!",
                         QMessageBox::Ok);
    ui->LoginButton->setDisabled(false);
    ui->statusLabel->clear();
}

void LoginDialog::on_LoginButton_clicked()
{
    QString userName = ui->userNameEdit->text();
    emit registerUserNameSignal(userName);
    ui->LoginButton->setDisabled(true);
    ui->statusLabel->setText("Connecting...");
}


void LoginDialog::on_ExitButton_clicked()
{
    emit exitSignal();
    this->close();
}

