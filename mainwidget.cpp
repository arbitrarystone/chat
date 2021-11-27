#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>
#include <QListWidget>
#include <QMouseEvent>
#include <QFont>
MainWidget::MainWidget(QWidget *parent) :
    QListWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

void MainWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

    this->itemAt(event->pos());
    secretUserId = this->itemAt(event->pos())->text();
    qDebug()<<"mouseDoubleClickevent"<<secretUserId;
    QDataStream in(&array,QIODevice::WriteOnly);
    in<<SECRETCHAT<<secretUserId;
    emit secretChatRequst(array);
}

MainWidget::~MainWidget()
{
    delete ui;

}


void MainWidget::initWidget(const QString userName)
{
    this->setStyleSheet("background-color:transparent");
    QString userId;
    for(int i=0;i<TcpConnect::userList.size();i++)
    {
        userId = TcpConnect::userList[i];
        QListWidgetItem *item = new QListWidgetItem(userId);
        item->setFlags(Qt::ItemIsEnabled);
        item->setFont(QFont("宋体",17,17));
        item->setTextAlignment(Qt::AlignHCenter);
        item->setSizeHint(QSize(20,20));
        this->insertItem(i,item);
    }
    this->setWindowTitle(userName);
    this->userName = userName;
    this->show();
}

void MainWidget::secretUserIsOnlineSlot(int status)
{
    if(status)
    {
        if(chatList.contains(secretUserId))
        {
            chatList[secretUserId]->raise();
            chatList[secretUserId]->activateWindow();
            chatList[secretUserId]->show();
        }
        else
        {
            chat = new chatWidget();
            connect(chat,&chatWidget::sendSignal,this,&MainWidget::msgFromChat);
            connect(this,&MainWidget::msgFromMainWindow,chat,&chatWidget::msgShow);
            chat->initWindow(userName,secretUserId);
            chatList[secretUserId] = chat;
        }
    }
    else
        QMessageBox::information(this,"离线","当前用户不在线",QMessageBox::Ok);
}


void MainWidget::chatMessageSlot(const QString& sender,const QString& msg)
{
    if(chatList.contains(sender))
    {
        chatList[sender]->raise();
        chatList[sender]->activateWindow();
        chat = chatList[sender];
        emit msgFromMainWindow(msg);
        chat->show();
    }
    else
    {
        chat = new chatWidget();
        connect(chat,&chatWidget::sendSignal,this,&MainWidget::msgFromChat);
        connect(this,&MainWidget::msgFromMainWindow,chat,&chatWidget::msgShow);
        chat->initWindow(userName,sender);
        emit msgFromMainWindow(msg);
        chatList[sender] = chat;

    }
}




