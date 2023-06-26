#include "send_page.h"
#include "ui_send_page.h"
#include "user_account.h"
#include "mythread.h"
#include <iostream>
send_page::send_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::send_page)
{
    ui->setupUi(this);
}

send_page::~send_page()
{
    delete ui;
}

void send_page::on_pushButton_clicked()
{
    if(MyThread::isOnline())
    {
        qDebug() << type_send;
        qDebug() << token;
        qDebug() << name_send;

        QUrl send("http://api.barafardayebehtar.ml:8080/sendmessage"+type_send+"?token="+token+"&dst="+name_send+"&body="+this->ui->lineEdit->text());
        qDebug() << send;
        MyThread *thread = new MyThread(send,this);
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
        thread->wait();

        QUrl send_2("http://api.barafardayebehtar.ml:8080/get"+type_send+"chats?token="+token+"&dst="+name_send);
        qDebug() << send_2;
        MyThread *thread_2 = new MyThread(send_2,this);
        connect(thread_2, SIGNAL(finished()), thread_2, SLOT(deleteLater()));
        thread_2->start();
        thread_2->wait();

        int first = 0 , last = 0;
        QJsonObject temp  = thread_2->jason_temp_thread;
        qDebug() << temp;
        std::string temp_string  = temp.value("message").toString().toStdString() , sub_str;
        int fin = temp_string.find("-");
        first = ++fin;
        while( temp_string[fin]!= '-')
        {
            fin++;
        }
        last = --fin;
        //int count = temp_string[fin] - '0';
        sub_str = temp_string.substr(first , last - first + 1);
        int count = stoi(sub_str);
        QString message = temp.value("message").toString();
        QString code = temp.value("code").toString();
        ui->plainTextEdit->clear();
        if (code == "200")
        {
            ui->lineEdit->clear();
            std::string temp_block = "block ";
            QString block ;
            QString src ,dst, body_main_message ,date , append_text;
            QJsonValue temp_messages;
            for(int i = 0 ; i < count ; i++)
            {
                temp_block = "block ";
                temp_block += std::to_string(i);
                block = "";append_text="";
                block = QString::fromStdString(temp_block);
                temp_messages = temp.value(block);
                QJsonObject body_obj = temp_messages.toObject();
                src = body_obj.value("src").toString();
                dst =  body_obj.value("dst").toString();
                body_main_message = body_obj.value("body").toString();
                date = body_obj.value("date").toString();
                ui->plainTextEdit->appendPlainText(src + " : " + body_main_message + "\n");
            }
        }
        if (code == "401")
            QMessageBox::warning(this , code , message);
    }

}

