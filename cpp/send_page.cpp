#include "..\header\send_page.h"
#include "ui_send_page.h"
#include "..\header\user_account.h"
#include "..\header\mythread.h"
#include <QFile>

using namespace std;
send_page::send_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::send_page)
{
    ui->setupUi(this);
    thread_sec = new get_thread();
    connect(thread_sec, SIGNAL(khalife()), this, SLOT(put()));
    connect(this, SIGNAL(starty()), this, SLOT(pakhsh()));
    this->setWindowTitle("Send Page");
    this->ui->pushButton->setDefault(1);
}

send_page::~send_page()
{
    delete ui;
}


void send_page::put()
{
    ui->lineEdit->show();
    ui->pushButton->show();
    if(MyThread::isOnline())
    {
    QUrl send_2("http://api.barafardayebehtar.ml:8080/get"+type_send+"chats?token="+token+"&dst="+contact_send);
    MyThread *thread_2 = new MyThread(send_2,this);
    connect(thread_2, SIGNAL(finished()), thread_2, SLOT(deleteLater()));
    thread_2->start();
    thread_2->wait();

    int first = 0 , last = 0;
    QJsonObject temp  = thread_2->jason_temp_thread;
    std::string temp_string  = temp.value("message").toString().toStdString() , sub_str;
    int fin = temp_string.find("-");
    first = ++fin;
    while( temp_string[fin]!= '-')
    {
        fin++;
    }
    last = --fin;
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
    }
}

void send_page::pakhsh()
{
    if(MyThread::isOnline())
    {
        thread_sec->start();
        put();
    }
    else
    {
        offlinemod();
    }

}

void send_page::offlinemod()
{
    ui->lineEdit->hide();
    ui->pushButton->hide();
    std::string file_path = __FILE__;
    std::string dir_path = file_path.substr(0, file_path.rfind("\\cpp"));
    dir_path = file_path.substr(0, file_path.rfind("\\cpp"));
    std::string address;
    if(type_send=="user")
        address = "Users";
    if(type_send=="group")
        address="Groups";
    if(type_send=="channel")
        address = "Channels";
    dir_path += "\\" + address + "\\" +contact_send.toStdString() + ".txt";
    ifstream test(dir_path);
    string tashkish;
    while(true)
    {
          test>>temp_mme.body;
          test>>tashkish;
          while(tashkish!="#^&*&^#"){
              temp_mme.body+=tashkish;
              test>>tashkish;
          }
          test>>temp_mme.src;
          if(test.eof())
              break;
          QString hasel=QString::fromStdString(temp_mme.src)+" : "+ QString::fromStdString(temp_mme.body)+"\n";
          ui->plainTextEdit->appendPlainText(hasel);
    }
}
void send_page::on_pushButton_clicked()
{
    try{
        if(ui->lineEdit->text() == "")
            throw std::invalid_argument("Nothing To Send");
        if(MyThread::isOnline())
        {
            QUrl send("http://api.barafardayebehtar.ml:8080/sendmessage"+type_send+"?token="+token+"&dst="+contact_send+"&body="+this->ui->lineEdit->text());
            MyThread *thread = new MyThread(send,this);
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            thread->start();
            thread->wait();
        }
    }
    catch (std::exception & e)
        {
            QMessageBox::warning(this , "Error" , e.what());
        }
}

void send_page::on_send_page_finished(int result)
{
    thread_sec->exit();
    ui->plainTextEdit->clear();
}

