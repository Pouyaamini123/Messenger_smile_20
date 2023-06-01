#include "mythread.h"

MyThread::MyThread(QUrl url,QObject *parent) :
    QThread(parent)
{
    this->temp = url;
}
void MyThread::run()
{

    qDebug() << " Thread started";
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(this->temp)); // Send GET request
    QObject::connect(reply, &QNetworkReply::finished, [&]()
     {
        if (reply->error() == QNetworkReply::NoError) {
            // If the request was successful, read the response
            QByteArray data = reply->readAll();
            qDebug() << "Response:" << data;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            //user_account user_account_object;
            jason_temp_thread = jsonObj;
            QString message = jsonObj.value("message").toString();
            QString code = jsonObj.value("code").toString();

            qDebug()<<"Message:"<<message<<", code: "<<code;
            this->exit();
        } else {
            // If there wa's an error, display the error message
            qDebug() << "Error:" << reply->errorString();
            this->exit();
        }

        // Cleanup the reply object and exit the application
        reply->deleteLater();
    });
    exec();
}

