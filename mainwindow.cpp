#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStyle>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sign_page = new Sign_Up_Page;
    user_page = new User_Page;
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
    if(MyThread::isOnline())
    {
        QUrl send("http://api.barafardayebehtar.ml:8080/login?username="+ui->lineEdit->text()+"&password="+ui->lineEdit_2->text());
        MyThread *thread = new MyThread(send,this);
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
        thread->wait();

        jason_asli_glob = thread->jason_temp_thread;

        password_glob = ui->lineEdit_2->text();;
        username_glob = ui->lineEdit->text();;



        QJsonObject temp  = thread->jason_temp_thread;
        token = temp.value("token").toString();
        QString message = temp.value("message").toString();
        QString code = temp.value("code").toString();
        if (code == "200")
        {
            QMessageBox::information(this , code , message);
            user_page->show();
            this->close();
        }

        if (code == "401")
            QMessageBox::warning(this , code , message);
        if(code=="404")
            QMessageBox::warning(this , code , message);
    }
    else
    {
        QMessageBox::warning(this , "InterNet Connection " ," You Are Not Connected To Interted");
    }


}

