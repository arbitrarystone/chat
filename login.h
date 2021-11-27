#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QString>
#include <QByteArray>
#include "configuration.h"
namespace Ui {
class Login;
}
class Login : public QWidget
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = 0);
    ~Login();
signals:
    void message(const QByteArray& array);
    void registerBtnSignal();
public slots:
     void loginBtnSlot();
    void registerBtnSlot();
    void errorSlot(const QString errorMessage);

private:
    Ui::Login *ui;
    QString password;
    QString userName;
    QByteArray array;
};

#endif // LOGIN_H
