#include "ChatWidget.h"
#include "ui_ChatWidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::on_pushButton_clicked()
{
    QString targetAccount = this->objectName().split('(').at(1).split(')').at(0);
    QString payload = ui->textEdit->toPlainText();
    ui->textEdit->clear();
    ui->textBrowser->append(QString("<font style=\"background:lightBlue\">"
                                        "%1"
                                        "</font><br />").arg(payload));
    emit sendMesgSignal(targetAccount, payload);
}

void ChatWidget::displayRecMesg(QString payload)
{
    ui->textBrowser->append(QString("<font style=\"background:lightgrey\">"
                                        "%1"
                                        "</font><br />").arg(payload));
}
