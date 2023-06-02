#include "user_page.h"
#include "ui_user_page.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "mythread.h"
#include "user_account.h"
QString ali;
User_Page::User_Page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User_Page)
{
    this->creat = 0;
    this->join = 0;
    this->list = 0;
    ui->setupUi(this);
    ui->groupBox->hide();
    ui->groupBox_4->hide();
    ui->groupBox_3->setCheckable(true);
    ui->groupBox_3->setChecked(false);
}

User_Page::~User_Page()
{
    delete ui;
}

void User_Page::on_pushButton_clicked()
{
   if(MyThread::isOnline())
    {
        QUrl send("http://api.barafardayebehtar.ml:8080/logout?username=" + username_glob +"&password="+password_glob);
        MyThread *thread = new MyThread(send,this);
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
        thread->wait();
        QJsonObject temp  = thread->jason_temp_thread;
        QString message = temp.value("message").toString();
        QString code = temp.value("code").toString();
        if (code == "200")
            QMessageBox::information(this , code , message);
        if (code == "401")
            QMessageBox::warning(this , code , message);
        ui->lineEdit_2->setText("");
        ui->lineEdit->setText("");
        this->close();
    }
   else
    {
        QMessageBox::warning(this , "InterNet Connection " ," You Are Not Connected To Interted");
    }
}


void User_Page::on_pushButton_5_clicked()
{
    if (creat == 0)
    {
        ui->groupBox_4->hide();
        ui->groupBox_5->hide();
        ui->groupBox->show();
        creat = 1;
    }
    else
    {
        ui->groupBox_5->hide();
        ui->groupBox_4->hide();
        ui->groupBox->hide();
         creat = 0;
    }
}


void User_Page::on_pushButton_3_clicked()
{
    if (join == 0)
    {
        ui->groupBox_4->show();
        ui->groupBox_5->hide();
        ui->groupBox->hide();
        join = 1;
    }
    else
    {
        ui->groupBox_5->hide();
        ui->groupBox_4->hide();
        ui->groupBox->hide();
         join = 0;
    }
}


void User_Page::on_pushButton_2_clicked()
{
    if (list == 0)
    {
        ui->groupBox_5->show();
        ui->groupBox_4->hide();
        ui->groupBox->hide();
        list = 1;
    }
    else
    {
         ui->groupBox_5->hide();
         ui->groupBox_4->hide();
         ui->groupBox->hide();
         list = 0;
    }
}

