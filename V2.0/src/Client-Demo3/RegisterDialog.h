#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class RegisterDialog;
}

/**
 * @brief The RegisterDialog class
 *        注册界面类
 */
class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

signals:
    /**
     * @brief registerVefSignal
     *        请求验证码
     * @param email 邮箱地址
     */
    void registerVefSignal(QString email);

    /**
     * @brief registerVefCheckSignal
     * @param email     邮箱地址
     * @param vef       验证码
     * @param username  用户名
     * @param passwd    设置的密码
     */
    void registerReqSignal(QString email, QString vef, QString username, QString passwd);

public slots:

    /**
     * @brief registerHandle
     *        处理Sign发出的切换窗口信号
     */
    void registerHandle();

    /**
     * @brief registerSucHandle
     *        处理Network发出的注册成功信号
     */
    void registerSucHandle();

    /**
     * @brief registerFaildHandle
     *        处理Network发出的注册失败信号
     */
    void registerFaildHandle();

private slots:
    /**
     * @brief on_ButtonRegister_clicked
     *        发起注册请求
     */
    void on_ButtonRegister_clicked();

    /**
     * @brief on_ButtonVerify_clicked
     *        获取注册验证码
     */
    void on_ButtonVerify_clicked();

    /**
     * @brief vefTimeoutHandle
     *        处理获取验证码冷却
     */
    void vefTimeoutHandle();

    /**
     * @brief reqTimeoutHandle
     *        处理注册请求超时
     */
    void reqTimeoutHandle();

private:
    Ui::RegisterDialog *ui;
    QTimer vefTimer;
    QTimer reqTimer;
};

#endif // REGISTERDIALOG_H
