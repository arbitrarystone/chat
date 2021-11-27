#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include <QWidget>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>
#include <QVector>
#include <QTimer>
#include "configuration.h"
class TcpConnect : public QWidget
{
    Q_OBJECT
public:
    static TcpConnect* getInstance();
    static QVector<QString> userList;
    QTimer m_Timer;

signals:
    void registerSucceed();
    void secretUserIsOnline(int status);
    void loginSucceed(const QString& userName);
    void loginError(const QString& errormessage);
    void registerError(const QString& errorMessage);
    void chatMessage(const QString& sender,const QString& msg);

public slots:
    void sendMessage(const QByteArray& array);
    void readMessage();
    void disconnectSlot();
    void connectSlot();
    void newConnect();
    void timerSlot();


private:
    static TcpConnect* instance;
    explicit TcpConnect(QWidget *parent = nullptr);
    ~TcpConnect();
    QString userName;
    QString sender;
    QTcpSocket* tcpSocket;
    QString errorMessage;
    QByteArray array;
    QString message;
    QString userId;
    int MessageType;
    int port;
    QString ip;
    bool isConnect;

};

#endif // TCPCONNECT_H
