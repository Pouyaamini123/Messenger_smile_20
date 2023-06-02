#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include "user_account.h"
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QUrl url,QObject *parent = nullptr);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    static bool isOnline();
private:
   QUrl temp;
public:
   QJsonObject jason_temp_thread;
};

#endif
