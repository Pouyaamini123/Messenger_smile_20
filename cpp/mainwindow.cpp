#include "..\header\mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStyle>
#include<windows.h>

using namespace std;
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sign_page = new Sign_Up_Page;
    user_page = new User_Page;
    ui->progressBar->hide();
    this->setWindowTitle("Main Window");
    setWindowIcon(QIcon("creat.png"));
    connect(this , SIGNAL(ready_write_file()) , this , SLOT(write_in_files()));
    this->ui->pushButton_2->setDefault(1);
    setWindowIcon(QIcon("../image/creat.png"));
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
   try {
        if(ui->lineEdit_2->text() == "" || ui->lineEdit->text() == "")
            throw std::invalid_argument("Name or Password is Empty");
        int i=0;
        int i1;
        i1=rand()%20+20;
        ui->progressBar->show();
        if(MyThread::isOnline())
        {
            for(i;i<=i1;i++)
            {
                Sleep(10);
                ui->progressBar->setValue(i);
            }

            user_name =ui->lineEdit->text();
            my_name=user_name;
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
                Sleep(10);
                ui->progressBar->setValue(i);
            }
            Sleep(50);

            QJsonObject temp  = thread->jason_temp_thread;
            token = temp.value("token").toString();
            QString message = temp.value("message").toString();
            QString code = temp.value("code").toString();
            if (code == "200")
            {
                if (message == "You are already logged in!")
                {
                    QUrl send_2("http://api.barafardayebehtar.ml:8080/logout?username="+ui->lineEdit->text()+"&password="+ui->lineEdit_2->text());
                    MyThread *thread_2 = new MyThread(send_2,this);
                    connect(thread_2, SIGNAL(finished()), thread_2, SLOT(deleteLater()));
                    thread_2->start();
                    thread_2->wait();

                    QUrl send_3("http://api.barafardayebehtar.ml:8080/login?username="+ui->lineEdit->text()+"&password="+ui->lineEdit_2->text());
                    MyThread *thread_3 = new MyThread(send_3,this);
                    connect(thread_3, SIGNAL(finished()), thread_3, SLOT(deleteLater()));
                    thread_3->start();
                    thread_3->wait();

                    jason_asli_glob = thread_3->jason_temp_thread;

                    password_glob = ui->lineEdit_2->text();;
                    username_glob = ui->lineEdit->text();;
                    QJsonObject temp_2  = thread_3->jason_temp_thread;
                    token = temp_2.value("token").toString();
                }
                for( i;i<101;i++)
                {
                    Sleep(10);
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
            ui->progressBar->setValue(0);
            emit ready_write_file();
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

void MainWindow::write_in_files()
{
    ptr = new thread_write();
    connect(ptr, SIGNAL(finished()), ptr, SLOT(deleteLater()));
    ptr->start();
  //  ptr->wait();
}



