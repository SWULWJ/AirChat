#ifndef ADDFRIENDDIALOG_H
#define ADDFRIENDDIALOG_H

#include <QDialog>

namespace Ui {
class AddFriendDialog;
}

class AddFriendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriendDialog(QWidget *parent = nullptr);
    ~AddFriendDialog();

signals:
    /**
     * @brief addFriendSignal
     *        发起添加好友请求
     * @param account
     */
    void addFriendSignal(QString account);

private slots:
    /**
     * @brief on_pushButton_clicked
     *        添加控件响应处理
     */
    void on_pushButton_clicked();

private:
    Ui::AddFriendDialog *ui;
};

#endif // ADDFRIENDDIALOG_H
