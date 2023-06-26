#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStyle>
#include<windows.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sign_page = new Sign_Up_Page;
    user_page = new User_Page;
    ui->progressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(MyThread::isOnline())
    {
        sign_page->show();
    }
    else
    {
        QMessageBox::warning(this , "InterNet Connection " ,"You Are Not Connected To Interted");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int i=0;
    int i1;
    i1=rand()%20+20;
    ui->progressBar->show();
    if(MyThread::isOnline())
    {
        for(i;i<=i1;i++)
        {
            Sleep(40);
            ui->progressBar->setValue(i);
        }
        user_name =ui->lineEdit->text();
        QUrl send("http://api.barafardayebehtar.ml:8080/login?username="+ui->lineEdit->text()+"&password="+ui->lineEdit_2->text());
        MyThread *thread = new MyThread(send,this);
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
        thread->wait();

        jason_asli_glob = thread->jason_temp_thread;

        password_glob = ui->lineEdit_2->text();;
        username_glob = ui->lineEdit->text();;
        i1=rand()%20+20+i1;
        for(i;i<=i1;i++)
        {
            Sleep(40);
            ui->progressBar->setValue(i);
        }
        Sleep(500);

        QJsonObject temp  = thread->jason_temp_thread;
        token = temp.value("token").toString();
        QString message = temp.value("message").toString();
        QString code = temp.value("code").toString();
        if (code == "200")
        {
            for( i;i<101;i++)
            {
                Sleep(40);
                ui->progressBar->setValue(i);
           }

            QMessageBox::information(this , code , message);
            user_page->show();
            this->close();
        }

        if (code == "401"){
            QMessageBox::warning(this , code , message);
            ui->progressBar->hide();
        }
        if(code=="404"){
            QMessageBox::warning(this , code , message);
            ui->progressBar->hide();
            ui->lineEdit_2->setText("");
            ui->lineEdit->setText("");
        }
    }
    else
    {
        QMessageBox::warning(this , "InterNet Connection " ," You Are Not Connected To Interted");
    }


}


