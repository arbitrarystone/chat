#include "tcpconnect.h"
#include <QDataStream>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
TcpConnect* TcpConnect::instance=NULL;
QVector<QString> TcpConnect::userList;
TcpConnect::TcpConnect(QWidget *parent) : QWidget(parent)
{
    port = 9999;
    ip ="192.168.185.2";
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,&QTcpSocket::readyRead,this,&TcpConnect::readMessage);
    connect(tcpSocket,&QTcpSocket::connected,this,&TcpConnect::connectSlot);
    connect(tcpSocket,&QTcpSocket::disconnected,this,&TcpConnect::disconnectSlot);
    connect(&m_Timer,&QTimer::timeout,this,&TcpConnect::timerSlot);
    newConnect();

}

TcpConnect::~TcpConnect()
{

    tcpSocket->disconnectFromHost();

}

TcpConnect* TcpConnect::getInstance()
{
    if(instance==NULL)
    {
        instance = new TcpConnect();
        qDebug()<<"连接";
    }
    return instance;
}

void TcpConnect::sendMessage(const QByteArray& array)
{
    tcpSocket->write(array);
}

void TcpConnect::readMessage()
{
    array = tcpSocket->readAll();
    QDataStream in(&array,QIODevice::ReadOnly);
    in>>MessageType>>message;
    switch(MessageType)
    {
    case LOGIN:
    {
        if(message =="succeed")//登陆成功
        {
            in>>userName;
            while(!in.atEnd())
            {
                in>>userId;
                userList.push_back(userId);
            }
            emit loginSucceed(userName);
        }
        else if(message =="error")//登陆失败
        {
            in>>errorMessage;
            emit loginError(errorMessage);
        }
        break;
    }
    case REGISTER:
    {
        if(message =="error")//注册失败
        {
            in>>errorMessage;
            emit registerError(errorMessage);
        }
        else if(message == "succeed")//注册成功
        {
            emit registerSucceed();
        }
        break;
    }
    case SECRETCHAT:
    {

        if(message=="succeed")
        {
            emit secretUserIsOnline(1);
        }
        else if(message == "error")
        {
            emit secretUserIsOnline(0);
        }
        break;

    }
    case CHATMESSAGE:
    {
        in>>sender;
        emit chatMessage(message,sender);
        break;
    }
    }

}


void TcpConnect::disconnectSlot()
{
    m_Timer.start(2000);
    isConnect = false;
}

void TcpConnect::connectSlot()
{
    m_Timer.stop();
    isConnect = true;
}

void TcpConnect::newConnect()
{
    tcpSocket->connectToHost(ip,port);
    if(!tcpSocket->waitForConnected(30000))
    {
        qDebug()<<"连接失败";
    }
    else
        qDebug()<<"连接成功";
}

void TcpConnect::timerSlot()
{
    if(!isConnect)
    {
        qDebug()<<"重连服务器中";
        newConnect();
    }
}

