#include <QApplication>
#include <QObject>
#include <QMessageBox>
#include "mainwidget.h"
#include "login.h"
#include "tcpconnect.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpConnect* tcpClient = TcpConnect::getInstance();
    Login login;
    Register reg;
    MainWidget listWidget;
    login.show();
    QObject::connect(&login,&Login::message,tcpClient,&TcpConnect::sendMessage);//登录消息发送
    QObject::connect(&reg,&Register::message,tcpClient,&TcpConnect::sendMessage);//注册消息发送
    QObject::connect(tcpClient,&TcpConnect::registerSucceed,&reg,&Register::registerSucceedSlot);
    QObject::connect(&login,&Login::registerBtnSignal,&reg,&Register::show);//注册按钮
    QObject::connect(tcpClient,&TcpConnect::registerSucceed,&login,&Login::show);//注册成功
    QObject::connect(tcpClient,&TcpConnect::registerError,&reg,&Register::errorSlot);//注册失败
    QObject::connect(tcpClient,&TcpConnect::loginSucceed,&listWidget,&MainWidget::initWidget);//登录成功
    QObject::connect(tcpClient,&TcpConnect::loginSucceed,&login,&Login::close);//登录成功后关闭登录页面
    QObject::connect(tcpClient,&TcpConnect::loginError,&login,&Login::errorSlot);//登录失败处理
    QObject::connect(&listWidget,&MainWidget::secretChatRequst,tcpClient,&TcpConnect::sendMessage);
    QObject::connect(tcpClient,&TcpConnect::secretUserIsOnline,&listWidget,&MainWidget::secretUserIsOnlineSlot);
    QObject::connect(tcpClient,&TcpConnect::chatMessage,&listWidget,&MainWidget::chatMessageSlot);
    QObject::connect(&listWidget,&MainWidget::msgFromChat,tcpClient,&TcpConnect::sendMessage);
    return a.exec();
}
