#include "mythread.h"
MyThread::MyThread(QUrl url,QObject *parent) :
    QThread(parent)
{
    this->temp = url;
}

void MyThread::run()
{
    qDebug() << " Thread started";
//    QUrl url("http://api.barafardayebehtar.ml:8080/login?username=ali&password=1234"); // The API endpoint to request
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

            QString title = jsonObj.value("message").toString();
            QString userId = jsonObj.value("code").toString();

            qDebug()<<"Message:"<<title<<", code: "<<userId;
        } else {
            // If there was an error, display the error message
            qDebug() << "Error:" << reply->errorString();
        }

        // Cleanup the reply object and exit the application
        reply->deleteLater();
    });
    exec();
}

//void MyThread::readyRead()
//{
//    QByteArray Data = socket->readAll();
//    qDebug() << socketDescriptor << " Data in: " << Data;
//    socket->write("\nThank You Client I Received Your Message :  " + Data);
//}
//void MyThread::disconnected()
//{
//    qDebug() << socketDescriptor << " Disconnected";
//    socket->deleteLater();
//    exit(0);
//}
