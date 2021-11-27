#include "chatwidget.h"
#include "ui_chatwidget.h"

chatWidget::chatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatWidget)
{
    ui->setupUi(this);

    connect(ui->sendBtn,&QPushButton::clicked,this,&chatWidget::sendBtnSlot);
}


chatWidget::~chatWidget()
{
    delete ui;
}

void chatWidget::initWindow(const QString &userName, const QString &secretUserId)
{
    this->userName = userName;
    this->secretId = secretUserId;
    this->setWindowTitle(secretUserId);
    this->show();
}

void chatWidget::sendBtnSlot()
{
    QDataStream out(&array,QIODevice::WriteOnly);
    if(ui->textEdit->toPlainText()!="")
    {
        sendMsg =  ui->textEdit->toPlainText();
        ui->textBrowser->append(userName+":");
        ui->textBrowser->append(sendMsg);
        ui->textEdit->clear();
        out<<CHATMESSAGE<<userName<<secretId<<sendMsg;
        emit sendSignal(array);
    }
}

void chatWidget::msgShow(const QString& msg)
{
    ui->textBrowser->append(secretId+":");
    ui->textBrowser->append(msg);
}
