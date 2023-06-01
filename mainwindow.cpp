#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user_account.h"
#include <QFile>
#include <QStyle>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    sign_page->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QUrl send("http://api.barafardayebehtar.ml:8080/login?username="+ui->lineEdit->text()+"&password="+ui->lineEdit_2->text());
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
    this->close();
    user_page->show();
}

