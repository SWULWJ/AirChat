#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTimer>

#include "logindialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChatWidget; }
QT_END_NAMESPACE

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();
    LoginDialog *loginDialog;

protected:
    QTcpSocket *tcpSocket;
    bool isConnect;
    QString userName;
    QTimer timer;
    QSet<QString> targetNameSet;
    static const QHostAddress serverIP;
    static const quint16 serverPort;

    QString mesgFormat(QString payload, QString targetName = "Server", QString serverMesgType = "");
    void registerUserNameHandle();
    void closeEvent(QCloseEvent *event) override;

protected slots:
    void disconnectedHandle();
    void connectedTimeoutHandle();
    void readyReadHandle();

public slots:
    void connectServerHandle(QString userName);
    void exitHandle();

signals:
    void connectedFailedSignal();
    void registerSuccessedSignal();
    void registerFailedSignal();

private slots:
    void on_sendButton_clicked();

private:
    Ui::ChatWidget *ui;
};
#endif // CHATWIDGET_H
