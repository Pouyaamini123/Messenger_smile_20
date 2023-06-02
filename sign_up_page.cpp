#include "sign_up_page.h"
#include "ui_sign_up_page.h"

Sign_Up_Page::Sign_Up_Page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sign_Up_Page)
{
    ui->setupUi(this);
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
   if(MyThread::isOnline()) {
        QUrl send("http://api.barafardayebehtar.ml:8080/signup?username="+ui->lineEdit->text()+"&password="+ui->lineEdit_2->text());
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



