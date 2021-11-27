#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include <QPushButton>
#include <QDataStream>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    connect(ui->registerBtn,&QPushButton::clicked,this,&Register::registerBtnSlot);
    connect(ui->closeBtn,&QPushButton::clicked,this,&Register::closeBtnSlot);
}

Register::~Register()
{
    delete ui;
}

void Register::closeBtnSlot()
{
    this->close();
    emit closeSignal();
}

void Register::registerBtnSlot()
{
    //用户名判断
    if(ui->userName->text().isEmpty())
        {
        QMessageBox::warning(this,QString("用户名不能为空"),QString("警告"));
    }
    else
        userName = ui->userName->text();
    //密码判断
    if(ui->password->text().isEmpty())
        QMessageBox::warning(this,QString("密码不能为空"),QString("警告"));
    else
        password = ui->password->text();
    //确认密码判断
    if(ui->confirmPassword->text().isEmpty())
        QMessageBox::warning(this,QString("确认密码不能为空"),QString("警告"));
    else if(ui->confirmPassword->text()!=password)
        QMessageBox::warning(this,QString("确认密码不一致,请重新输入"),QString("警告"));
    //性别判断
    sex = ui->sex->currentText();
    if(ui->emailAddr->text().isEmpty())
        {
        QMessageBox::warning(this,QString("邮箱地址不能为空"),QString("警告"));
    }
    else
        emailAddr = ui->emailAddr->text();

    QDataStream out(&array,QIODevice::WriteOnly);
    out<<REGISTER<<userName<<password<<emailAddr<<sex;
    emit message(array);

}

void Register::registerSucceedSlot()
{
    QMessageBox::information(this,QString("注册成功"),"注册成功,请重新登录");
    this->close();
}

void Register::errorSlot(const QString errorMessage)
{
        QMessageBox::information(this,"注册失败",errorMessage,QMessageBox::Ok);

}
