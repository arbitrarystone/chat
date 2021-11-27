#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QString>
#include <QListWidgetItem>
#include <QListWidget>
#include <QMap>
#include <QEvent>
#include <QByteArray>
#include "chatwidget.h"
#include "tcpconnect.h"
#include "register.h"
#include "login.h"
#include "configuration.h"
namespace Ui {
class MainWidget;
}

class MainWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
     void mouseDoubleClickEvent(QMouseEvent *event);
    ~MainWidget();
signals:
    void msgFromChat(const QByteArray& array);
    void msgFromMainWindow(const QString& msg);
    void secretChatRequst(const QByteArray& array);
public slots:
    void initWidget(const QString userName);
    void secretUserIsOnlineSlot(int status);
    void chatMessageSlot(const QString& sender,const QString& msg);
private:
    Ui::MainWidget *ui;
    QString secretUserId;
    QString userName;
    QMap<QString,chatWidget*> chatList;
    QByteArray array;
    chatWidget* chat;
};





#endif // MAINWIDGET_H
