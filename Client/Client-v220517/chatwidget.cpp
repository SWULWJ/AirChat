#include "chatwidget.h"
#include "ui_chatwidget.h"

#include <QHostAddress>
#include <QMessageBox>
#include <QCloseEvent>

const QHostAddress ChatWidget::serverIP = QHostAddress("xxx.xxx.xxx.xxx");
const quint16 ChatWidget::serverPort = 0000;

ChatWidget::ChatWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    tcpSocket = nullptr;
    isConnect = false;
    userName = nullptr;
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::connectServerHandle(QString userName)
{
    this->userName = userName;
    if(isConnect != true)
    {
        if(tcpSocket == nullptr)
        {
            tcpSocket = new QTcpSocket(this);
        }
        connect(tcpSocket, &QTcpSocket::connected, this, &ChatWidget::registerUserNameHandle);
        connect(&timer, &QTimer::timeout, this, &ChatWidget::connectedTimeoutHandle);
        connect(tcpSocket, &QTcpSocket::readyRead, this, &ChatWidget::readyReadHandle);
        tcpSocket->connectToHost(serverIP, serverPort);
        if(timer.isActive() != true)
        {
            timer.start(10000);
        }
    }
    else
    {
        registerUserNameHandle();
    }
}

void ChatWidget::readyReadHandle()
{
    QString mesg = tcpSocket->readAll();
    QString targetName = mesg.left(15).trimmed();
    QString payload = mesg.mid(31);
    if(targetName == "Server")
    {
        QString serverMesgType = payload.left(20).trimmed();
        //Server@userNameRegisterSuccessful
        if(serverMesgType == "RegisterSuccessful")//18
        {
            ui->userNameLabel->setText(userName);
            show();
            emit registerSuccessedSignal();
        }
        //Server@userNameRegisterFailed
        else if(serverMesgType == "RegisterFailed")//14
        {
            emit registerFailedSignal();
        }
        //Server@userNameTargetOfflineTargetName
        else if(serverMesgType == "TargetOffline")//15
        {
            QString offlineTarget = payload.mid(20);
            QString showMesg = QString("[Server]: \"%1\" is offline!").arg(offlineTarget);
            ui->Browser->append(showMesg);
            //remove form comboBox
            if(targetNameSet.contains(offlineTarget) == true)
            {
                for(int i = 0; i < ui->targetNameComboBox->count(); ++i)
                {
                    if(ui->targetNameComboBox->itemText(i) == offlineTarget)
                    {
                        ui->targetNameComboBox->removeItem(i);
                        break;
                    }
                }
                targetNameSet.remove(offlineTarget);
            }
        }
    }
    else
    {
        payload = payload.trimmed();
        QString showMesg = QString("[%1]: %2").arg(targetName, payload);
        ui->Browser->append(showMesg);
        if(targetNameSet.contains(targetName) != true)
        {
            ui->targetNameComboBox->addItem(targetName);
        }
    }
}

void ChatWidget::connectedTimeoutHandle()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    timer.stop();
    emit connectedFailedSignal();
}

void ChatWidget::registerUserNameHandle()
{
    timer.stop();
    isConnect = true;
    connect(tcpSocket, &QTcpSocket::disconnected, this, &ChatWidget::disconnectedHandle);
    QString mesg = mesgFormat("", "Server", "Register");
    tcpSocket->write(mesg.toUtf8().data());
}

void ChatWidget::exitHandle()
{
    timer.stop();
    isConnect = false;
    if(tcpSocket != nullptr)
    {
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
    }
    this->close();
}

void ChatWidget::disconnectedHandle()
{
    isConnect = false;
    QMessageBox::warning(this,
                         "Warning",
                         "Disconnect from the server",
                         QMessageBox::Ok);
    loginDialog->show();
    hide();
}

void ChatWidget::on_sendButton_clicked()
{
    QString targetName = ui->targetNameComboBox->currentText();
    if(targetName.compare("Server") == 0)
    {
        return;
    }
    if(targetNameSet.contains(targetName) != true)
    {
        targetNameSet.insert(targetName);
        ui->targetNameComboBox->addItem(targetName);
    }
    QString payload = ui->Edit->toPlainText();
    QString mesg = mesgFormat(payload, targetName);
    tcpSocket->write(mesg.toUtf8().data());
    ui->Browser->append(QString("to [%1]: %2").arg(targetName, payload));
    ui->Edit->clear();
}

void ChatWidget::closeEvent(QCloseEvent *event)
{
    disconnect(tcpSocket, &QTcpSocket::disconnected, this, &ChatWidget::disconnectedHandle);
    timer.stop();
    isConnect = false;
    if(tcpSocket != nullptr)
    {
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
    }
    event->accept();
}

QString ChatWidget::mesgFormat(QString payload, QString targetName, QString serverMesgType)
{
    QString mesg;
    if(targetName == "Server" && serverMesgType != "")
    {
        mesg = QString("%1@%2%3").arg(userName, 15)
                                 .arg("Server", 15)
                                 .arg(serverMesgType, 20);
    }
    else if(targetName != "Server" && serverMesgType == "")
    {
        mesg = QString("%1@%2%3").arg(userName, 15)
                                 .arg(targetName, 15)
                                 .arg(payload);
    }
    return mesg;
}
