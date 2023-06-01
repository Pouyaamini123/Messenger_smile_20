#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h""
#include <QFile>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sign_page = new Sign_Up_Page;
    user = new User_Page;
   /* QFile file("Chatbee.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);*/
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
    thread->run();
}

