#include "chatwidget.h"
#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);
    ChatWidget w;
    LoginDialog *L = new LoginDialog();

    L->setWindowFlags(Qt::WindowCloseButtonHint);
    w.loginDialog = L;

    QObject::connect(L, &LoginDialog::registerUserNameSignal, &w, &ChatWidget::connectServerHandle);
    QObject::connect(L, &LoginDialog::exitSignal, &w, &ChatWidget::exitHandle);
    QObject::connect(&w, &ChatWidget::registerSuccessedSignal, L, &LoginDialog::registerSucccessedHandle);
    QObject::connect(&w, &ChatWidget::registerFailedSignal, L, &LoginDialog::registerFailedHandle);
    QObject::connect(&w, &ChatWidget::connectedFailedSignal, L, &LoginDialog::connectedFailedhandle);

//    w.show();
    L->show();
    return a.exec();
}
