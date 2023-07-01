#ifndef SIGNINDIALOG_H
#define SIGNINDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class SignInDialog;
}

/**
 * @brief The LoginDialog class
 *        登录界面类
 */
class SignInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignInDialog(QWidget *parent = nullptr);
    ~SignInDialog();

signals:
    /**
     * @brief signInReqSignal
     *        登录请求信号
     * @param account   账号
     * @param passwd    密码
     */
    void signInReqSignal(QString account, QString passwd);

    /**
     * @brief registerSignal
     *        注册界面切换信号
     */
    void registerSignal();

public slots:
    /**
     * @brief signInSucInitHandle
     *        处理Network发出的登录成功信号
     */
    void signInSucHandle();

    /**
     * @brief signInFaildHandle
     *        处理Network发出的登录失败信号
     */
    void signInFaildHandle();

protected:
    /**
     * @brief eventFilter
     *        处理"label-注册账号"点击事件
     * @param obj
     * @param event
     * @return
     */
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:

    /**
     * @brief on_ButtonSignIn_clicked
     *        处理"登录"控件点击
     */
    void on_ButtonSignIn_clicked();

    /**
     * @brief timeoutHandle
     *        登录超时响应处理
     */
    void timeoutHandle();

private:
    Ui::SignInDialog *ui;
    QTimer timer;
};

#endif // SIGNINDIALOG_H
