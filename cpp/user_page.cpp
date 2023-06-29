#include "..\header\user_page.h"
#include "ui_user_page.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "..\header\mythread.h"
#include "..\header\user_account.h"

User_Page::User_Page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User_Page)
{
    send_p = new send_page;
    this->creat = 0;
    this->join = 0;
    this->list = 0;
    this->sendd=0;
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
        if (code == "200"){
            QMessageBox::information(this , code , message);
        this->close();}
        if (code == "401")
            QMessageBox::warning(this , code , message);
        ui->lineEdit_2->setText("");
        ui->lineEdit->setText("");

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
        ui->groupBox_6->hide();
        ui->groupBox_4->hide();
        ui->groupBox_5->hide();
        ui->groupBox->show();
        creat = 1;
    }
    else
    {
        ui->groupBox_6->hide();
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
        ui->groupBox_6->hide();
        ui->groupBox_4->show();
        ui->groupBox_5->hide();
        ui->groupBox->hide();
        join = 1;
    }
    else
    {
        ui->groupBox_6->hide();
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
        ui->groupBox_6->hide();
        ui->groupBox_5->show();
        ui->groupBox_4->hide();
        ui->groupBox->hide();
        list = 1;
    }
    else
    {
        ui->groupBox_6->hide();
         ui->groupBox_5->hide();
         ui->groupBox_4->hide();
         ui->groupBox->hide();
         list = 0;
    }
}


void User_Page::on_pushButton_7_clicked()// list
{
    QString typy , address;
    if(ui->comboBox_3->currentText()=="Channel" )
    {
        typy = "channel";
    }
    else if(ui->comboBox_3->currentText()=="Group")
    {
        typy = "group";
    }
    else if(ui->comboBox_3->currentText()=="User")
    {
        typy = "user";
    }
    if(MyThread::isOnline())
    {
         address = "http://api.barafardayebehtar.ml:8080/get" + typy +"list?token=" +token;
         QUrl send(address);
         MyThread *thread = new MyThread(send,this);
         connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
         thread->start();
         thread->wait();
         QJsonObject temp  = thread->jason_temp_thread , channel_mes;
         QString message = temp.value("message").toString();
         QString code = temp.value("code").toString();
         if (code == "200")
         {
             std::string temp_string = message.toStdString();
             int find = temp_string.find("-");
             int count = temp_string[find+1] - '0';
             std::string block = "block ";
             QString  value, text;
             //char number;
             for(int i = 0 ; i < count ; i++)
             {
                 block += (i + '0');
                 value = QString::fromStdString(block);
                 //number = i + '0';
                 channel_mes = temp.value(value).toObject();

                 text = channel_mes.value("channel_name").toString();

                 ui->textEdit->insertPlainText(text + "\n");
                 block = "block ";
             }

         }
         if (code == "204")
            {
              QMessageBox::warning(this , code , message);
            }
         if (code == "404")
            {
             QMessageBox::warning(this , code , message);
             }
         if (code == "401")
         {
             QMessageBox::warning(this , code , message);
         }
     }
    else
    {
        QMessageBox::warning(this , "InterNet Connection " ," You Are Not Connected To Interted");
    }
}


void User_Page::on_pushButton_8_clicked() // join
{
    QString typy , address;
    if(ui->comboBox_2->currentText()=="Channel" )
    {
        typy = "channel";
    }

    else if(ui->comboBox_2->currentText()=="Group")
    {
        typy = "group";
    }
    if(MyThread::isOnline())
    {
         address = "http://api.barafardayebehtar.ml:8080/join" + typy + "?token=" +token+ "&" + typy+"_name=" + ui->lineEdit_3->text();
         QUrl send(address);
         MyThread *thread = new MyThread(send,this);
         connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
         thread->start();
         thread->wait();
         QJsonObject temp  = thread->jason_temp_thread;
         QString message = temp.value("message").toString();
         QString code = temp.value("code").toString();
         if (code == "200"){
             QMessageBox::information(this , code , message);
         }
         if (code == "204")
            { QMessageBox::warning(this , code , message);
         ui->lineEdit_2->setText("");}
         if (code == "404")
            { QMessageBox::warning(this , code , message);
         ui->lineEdit->setText("");
         }
         if (code == "401")
         {
             QMessageBox::warning(this , code , message);
             ui->lineEdit->setText("");
         }
     }
    else
    {
        QMessageBox::warning(this , "InterNet Connection " ," You Are Not Connected To Interted");
    }
}


void User_Page::on_pushButton_6_clicked()
{
    QString typy , address;
    if(ui->comboBox->currentText()=="Channel")
    {
        typy = "channel";
    }
    else if(ui->comboBox->currentText()=="Group")
    {
        typy = "group";
    }
    if(MyThread::isOnline())
    {
         address = "http://api.barafardayebehtar.ml:8080/create" + typy + "?token=" +token+"&" + typy + "_name=" + ui->lineEdit->text() + "&" + typy+"_title="+ui->lineEdit_2->text();
         QUrl send(address);
         MyThread *thread = new MyThread(send,this);
         connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
         thread->start();
         thread->wait();
         QJsonObject temp  = thread->jason_temp_thread;
         QString message = temp.value("message").toString();
         QString code = temp.value("code").toString();
         if (code == "200")
         {
             QMessageBox::information(this , code , message);
         }
         if (code == "204")
         {
             QMessageBox::warning(this , code , message);
             ui->lineEdit_2->setText("");
         }
         if (code == "404")
         {
             QMessageBox::warning(this , code , message);
             ui->lineEdit->setText("");
         }
         if (code == "401")
         {
             QMessageBox::warning(this , code , message);
             ui->lineEdit->setText("");
         }
    }
    else
    {
        QMessageBox::warning(this , "InterNet Connection " ," You Are Not Connected To Interted");
    }
}

void User_Page::on_pushButton_4_clicked()
{
    if (sendd == 0)
    {
        ui->groupBox_6->show();
        ui->groupBox_4->hide();
        ui->groupBox_5->hide();
        ui->groupBox->hide();
        sendd = 1;
    }
    else
    {
         ui->groupBox_6->hide();
         ui->groupBox_5->hide();
         ui->groupBox_4->hide();
         ui->groupBox->hide();
         sendd = 0;
    }
}


void User_Page::on_pushButton_14_clicked()
{
    type_send = ui->comboBox_4->currentText();
    contact_send = ui->lineEdit_4->text();
    send_p->show();
    emit send_p->starty();
}

