#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();
    /**
     * @brief displayRecMesg
     *        显示接受到的消息
     * @param payload
     */
    void displayRecMesg(QString payload);

signals:
    /**
     * @brief sendMesgSignal
     *        发起发送消息请求信号
     * @param targetAccount
     * @param payload
     */
    void sendMesgSignal(QString targetAccount, QString payload);

private slots:
    /**
     * @brief on_pushButton_clicked
     *        发送控件响应处理
     */
    void on_pushButton_clicked();

private:
    Ui::ChatWidget *ui;
};

#endif // CHATWIDGET_H
