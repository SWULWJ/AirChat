#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

public slots:
    void connectedFailedhandle();
    void registerSucccessedHandle();
    void registerFailedHandle();

signals:
    void registerUserNameSignal(QString userName);
    void exitSignal();

private slots:
    void on_LoginButton_clicked();

    void on_ExitButton_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
