#include "..\header\sign_up_page.h"
#include "ui_sign_up_page.h"
#include<windows.h>
#include<iostream>

Sign_Up_Page::Sign_Up_Page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sign_Up_Page)
{
    ui->setupUi(this);
    this->setWindowTitle("Sign up Page");
    this->ui->pushButton_3->setDefault(1);
}

Sign_Up_Page::~Sign_Up_Page()
{
    delete ui;
}

void Sign_Up_Page::on_pushButton_2_clicked()
{
    ui->lineEdit_2->setText("");
    ui->lineEdit->setText("");
    this->close();

}

void Sign_Up_Page::on_pushButton_3_clicked()
{
 try
    {
        if(ui->lineEdit_2->text() == "" || ui->lineEdit->text() == "")
            throw std::invalid_argument("Name or Password is Empty");
    int i=0;
    int i1;
    i1=rand()%20+20;
    ui->progressBar_1->show();
   if(MyThread::isOnline())
   {
       for(i;i<=i1;i++)
       {
           Sleep(10);
           ui->progressBar_1->setValue(i);
       }

        QUrl send("http://api.barafardayebehtar.ml:8080/signup?username="+ui->lineEdit->text()+"&password="+ui->lineEdit_2->text());
        MyThread *thread = new MyThread(send,this);
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        i1=rand()%20+20+i1;
        for(i;i<=i1;i++)
        {
            Sleep(10);
            ui->progressBar_1->setValue(i);
        }
        Sleep(50);

        thread->start();
        thread->wait();
        QJsonObject temp  = thread->jason_temp_thread;
        QString message = temp.value("message").toString();
        QString code = temp.value("code").toString();
        if (code == "200"){
            for( i;i<101;i++)
            {
                Sleep(10);
                ui->progressBar_1->setValue(i);
           }
            QMessageBox::information(this , code , message);
            this->close();
        }
        if (code== "204")
            QMessageBox::warning(this , code , message);
        ui->lineEdit_2->setText("");
        ui->lineEdit->setText("");
        ui->progressBar_1->setValue(0);
        ui->progressBar_1->setValue(0);
    }
       else
       {
           QMessageBox::warning(this , "InterNet Connection " ," You Are Not Connected To Interted");
       }
}
catch (std::exception & e)
    {
        QMessageBox::warning(this , "Error" , e.what());
    }
}



