#include "AddFriendDialog.h"
#include "ui_AddFriendDialog.h"

AddFriendDialog::AddFriendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFriendDialog)
{
    ui->setupUi(this);
}

AddFriendDialog::~AddFriendDialog()
{
    delete ui;
}

void AddFriendDialog::on_pushButton_clicked()
{
    QString account = ui->EditAccount->text();
    emit addFriendSignal(account);
    close();
}
