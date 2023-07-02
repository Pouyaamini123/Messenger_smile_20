#include "..\header\mythread.h"

MyThread::MyThread(QUrl url,QObject *parent) :
    QThread(parent)
{
    this->temp = url;
}
void MyThread::run()
{

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(this->temp)); // Send GET request
    QObject::connect(reply, &QNetworkReply::finished, [&]()
     {
        if (reply->error() == QNetworkReply::NoError) {
            // If the request was successful, read the response
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            //user_account user_account_object;

            //this->jason_asli_glob = jsonObj;

            jason_temp_thread = jsonObj;
            QString message = jsonObj.value("message").toString();
            QString code = jsonObj.value("code").toString();


            this->exit();
        } else {
            // If there wa's an error, display the error message

            this->exit();
        }

        // Cleanup the reply object and exit the application
        reply->deleteLater();
    });
    exec();
}

bool MyThread::isOnline()
{
    bool retVal = false;
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply* reply = nam.get(req);
    QEventLoop loop;
    QTimer timeoutTimer;
    connect(&timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
//    timeoutTimer.setSingleShot(true);
//    timeoutTimer.start(100000);
    loop.exec();
    if (reply->bytesAvailable())
    {
        retVal = true;
    }
    return retVal;
}

