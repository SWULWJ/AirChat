#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    void init(QString ip, quint16 port);

private:
    QString serverIP;
    quint16 serverPort;
    bool isConnected;

protected slots:
    /**
     * @brief readyReadHandle
     */
    void readyReadHandle();

    /**
     * @brief disconnectedHandle
     */
    void disconnectedHandle();

public slots:
    /**
     * @brief sendHandle
     *        发送数据
     * @param mesg
     */
    void sendHandle(char* mesg);

signals:
    /**
     * @brief newMesg
     *        新消息到达信号
     * @param mesg
     */
    void newMesg(QString mesg);

};

#endif // MYTCPSOCKET_H
