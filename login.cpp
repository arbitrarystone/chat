#include "login.h"
#include "ui_login.h"
#include <QPushButton>
#include <QDataStream>
#include <QMessageBox>
#include <QDebug>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->BtnLogin,&QPushButton::clicked,this,&Login::loginBtnSlot);//点击登录按钮进入发送消息槽函数
    connect(ui->BtnRegister,&QPushButton::clicked,this,&Login::registerBtnSlot);

}

Login::~Login()
{
    delete ui;
}

void Login::loginBtnSlot()
{
    userName = ui->userName->text();
    password = ui->password->text();
    QDataStream out(&array,QIODevice::WriteOnly);
    out<<LOGIN<<userName<<password;
    emit message(array);//发送包含消息的信号
}

void Login::registerBtnSlot()
{
    this->hide();
    emit registerBtnSignal();

}

void Login::errorSlot(const QString errorMessage)
{
    QMessageBox::information(this,"错误",errorMessage);

}

