QT       += core gui \
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddFriendDialog.cpp \
    ChatMainWindow.cpp \
    ChatWidget.cpp \
    MyTcpSocket.cpp \
    NetworkBusiness.cpp \
    RegisterDialog.cpp \
    SignInDialog.cpp \
    main.cpp

HEADERS += \
    AddFriendDialog.h \
    ChatMainWindow.h \
    ChatWidget.h \
    MyTcpSocket.h \
    NetworkBusiness.h \
    RegisterDialog.h \
    SignInDialog.h

FORMS += \
    AddFriendDialog.ui \
    ChatMainWindow.ui \
    ChatWidget.ui \
    RegisterDialog.ui \
    SignInDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    WinHighDPI.qrc
