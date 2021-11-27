#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include "configuration.h"
namespace Ui {
class chatWidget;
}

class chatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit chatWidget(QWidget *parent = nullptr);
    ~chatWidget();
    QString userName;
    QString secretId;
    QByteArray array;
    void initWindow(const QString &userName,const QString &secretUserId);
signals:
    void sendSignal(const QByteArray& array);
public slots:
    void sendBtnSlot();
    void msgShow(const QString& msg);
private:
    Ui::chatWidget *ui;
    QString sendMsg;
    QString recvMsg;
};

#endif // CHATWIDGET_H
