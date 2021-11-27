#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QString>
#include <QByteArray>
#include "configuration.h"
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT
public:
    explicit Register(QWidget *parent = 0);
    ~Register();
signals:
    void message(const QByteArray& array);
    void closeSignal();
public slots:
    void closeBtnSlot();
    void registerBtnSlot();
    void registerSucceedSlot();
    void errorSlot(const QString errorMessage);

private:
    Ui::Register *ui;
    QString userName;
    QString password;
    QString emailAddr;
    QString sex;
    QByteArray array;
};

#endif // REGISTER_H
