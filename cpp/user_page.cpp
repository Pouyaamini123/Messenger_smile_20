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
#include <experimental/filesystem>
#include<windows.h>

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
    this->setWindowTitle("User Page");
}

User_Page::~User_Page()
{
    delete ui;
}

void User_Page::on_pushButton_clicked()
{
    on_User_Page_finished(0);
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
    ui->textEdit->clear();
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
    ui->textEdit->clear();
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
    ui->textEdit->clear();
}


void User_Page::on_pushButton_7_clicked()
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
            address = "http://api.barafardayebehtar.ml:8080/get" + typy +"list?token=" +token;
            QUrl send(address);
            MyThread *thread = new MyThread(send);
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            thread->start();
            thread->wait();

            int first = 0 , last = 0;
            QJsonObject temp  = thread->jason_temp_thread , object_mes;
            QString message = temp.value("message").toString();
            QString code = temp.value("code").toString();
            if (code == "200")
            {
                for( i;i<101;i++)
                {
                    Sleep(10);
                    ui->progressBar->setValue(i);
                }
                std::string temp_string = message.toStdString(),sub_str;
                int fin = temp_string.find("-");
                first = ++fin;
                while( temp_string[fin]!= '-')
                {
                    fin++;
                }
                last = --fin;
                sub_str = temp_string.substr(first , last - first + 1);
                int count = stoi(sub_str);
                std::string block = "block ";
                QString  value, text;
                ui->textEdit->clear();
                for(int i = 0 ; i < count ; i++)
                {
                    block += (i + '0');
                    value = QString::fromStdString(block);
                    object_mes = temp.value(value).toObject();
                    if(typy != "user")
                        text = object_mes.value(typy + "_name").toString();
                    else
                        text = object_mes.value("src").toString();


                    ui->textEdit->append(text+"\n");

                    block = "block ";
                }

            }
                      if (code == "204")
                          QMessageBox::warning(this , code , message);
                      if (code == "404")
                          QMessageBox::warning(this , code , message);
                      if (code == "401")
                          QMessageBox::warning(this , code , message);

        }
        else
        {
             QMessageBox::warning(this , "InterNet Connection " ," You Are Not Connected To Interted");
        }
        ui->progressBar->setValue(0);
    }


void User_Page::on_pushButton_8_clicked()
{
   try {
        if(ui->lineEdit_3->text() == "" )
            throw std::invalid_argument("Name is Empty");
        QString typy , address;
        if(ui->comboBox_2->currentText()=="Channel" )
        {

            typy = "channel";
        }

        else if(ui->comboBox_2->currentText()=="Group")
        {
            typy = "group";
        }
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

            address = "http://api.barafardayebehtar.ml:8080/join" + typy + "?token=" +token+ "&" + typy+"_name=" + ui->lineEdit_3->text();
            QUrl send(address);
            MyThread *thread = new MyThread(send);
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            thread->start();
            thread->wait();
            i1=rand()%20+20+i1;
            for(i;i<=i1;i++)
            {
                Sleep(10);
                ui->progressBar->setValue(i);
            }
            Sleep(50);
            QJsonObject temp  = thread->jason_temp_thread;
            QString message = temp.value("message").toString();
            QString code = temp.value("code").toString();
            if (code == "200"){
                for( i;i<101;i++)
                {
                    Sleep(10);
                    ui->progressBar->setValue(i);
                }
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
            ui->progressBar->setValue(0);
        }
        else
        {
            QMessageBox::warning(this , "InterNet Connection " ," You Are Not Connected To Interted");
        }
        ui->lineEdit_3->clear();
    }catch (std::exception & e)
    {
        QMessageBox::warning(this , "Error" , e.what());
    }
}


void User_Page::on_pushButton_6_clicked() //creat
{
   try {
        if(ui->lineEdit->text() == "")
            throw std::invalid_argument("Name is Empty");

        QString typy , address;
        if(ui->comboBox->currentText()=="Channel")
        {
            typy = "channel";
        }
        else if(ui->comboBox->currentText()=="Group")
        {
            typy = "group";
        }
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
            address = "http://api.barafardayebehtar.ml:8080/create" + typy + "?token=" +token+"&" + typy + "_name=" + ui->lineEdit->text() + "&" + typy+"_title="+ui->lineEdit_2->text();
            QUrl send(address);
            MyThread *thread = new MyThread(send);
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            thread->start();
            thread->wait();
            i1=rand()%20+20+i1;
            for(i;i<=i1;i++)
            {
                Sleep(10);
                ui->progressBar->setValue(i);
            }
            Sleep(50);
            QJsonObject temp  = thread->jason_temp_thread;
            QString message = temp.value("message").toString();
            QString code = temp.value("code").toString();
            if (code == "200")
            {
                for( i;i<101;i++)
                {
                    Sleep(10);
                    ui->progressBar->setValue(i);
                }
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
        ui->lineEdit->clear();
        ui->progressBar->setValue(0);
    }
    catch (std::exception & e)
        {
            QMessageBox::warning(this , "Error" , e.what());
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
    ui->textEdit->clear();
}


void User_Page::on_pushButton_14_clicked() // send
{
    try{
        if(ui->lineEdit_4->text() == "" )
            throw std::invalid_argument("Name is Empty");
        type_send = ui->comboBox_4->currentText();
        contact_send = ui->lineEdit_4->text();
        int state=0;
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
            if(type_send=="user")
            {
                QUrl send("http://api.barafardayebehtar.ml:8080/login?username="+contact_send+"&password=a#^&*&^#a");
                MyThread *thread = new MyThread(send,this);
                connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
                thread->start();
                thread->wait();
                i1=rand()%20+20+i1;
                for(i;i<=i1;i++)
                {
                    Sleep(10);
                    ui->progressBar->setValue(i);
                }
                Sleep(50);

                QJsonObject temp  = thread->jason_temp_thread;
                QString message = temp.value("message").toString();
                QString code = temp.value("code").toString();
                if(code=="404")
                    QMessageBox::information(this ,code, message);
                else
                    state=1;
            }


            if(type_send=="group")
            {
                QString  addressy;
                addressy = "http://api.barafardayebehtar.ml:8080/getgrouplist?token=" +token;
                QUrl send(addressy);
                MyThread *thread = new MyThread(send);
                connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
                thread->start();
                thread->wait();
                i1=rand()%20+20+i1;
                for(i;i<=i1;i++)
                {
                    Sleep(10);
                    ui->progressBar->setValue(i);
                }
                Sleep(50);

                int first = 0 , last = 0;
                QJsonObject temp  = thread->jason_temp_thread , object_mes;
                QString message = temp.value("message").toString();
                QString code = temp.value("code").toString();
                if (code == "200")
                {
                    std::string temp_string = message.toStdString(),sub_str;
                    int fin = temp_string.find("-");
                    first = ++fin;
                    while( temp_string[fin]!= '-')
                    {
                        fin++;
                    }
                    last = --fin;
                    sub_str = temp_string.substr(first , last - first + 1);
                    int count = stoi(sub_str);
                    std::string block = "block ";
                    QString  value, text;
                    for(int i = 0 ; i < count ; i++)
                    {
                        block += (i + '0');
                        value = QString::fromStdString(block);
                        object_mes = temp.value(value).toObject();
                        text = object_mes.value("group_name").toString();
                        block = "block ";
                        if(contact_send == text)
                        {
                            state=1;
                        }
                    }
                    if(state == 0)
                    {
                        QMessageBox::warning(this ,"Error", "You have not joined the group yet");
                    }
                }

            }

            if(type_send=="channel")
            {
                QString  addressy;
                addressy = "http://api.barafardayebehtar.ml:8080/getchannellist?token=" +token;
                QUrl send(addressy);
                MyThread *thread = new MyThread(send);
                connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
                thread->start();
                thread->wait();
                i1=rand()%20+20+i1;
                for(i;i<=i1;i++)
                {
                    Sleep(10);
                    ui->progressBar->setValue(i);
                }
                Sleep(50);

                int first = 0 , last = 0;
                QJsonObject temp  = thread->jason_temp_thread , object_mes;
                QString message = temp.value("message").toString();
                QString code = temp.value("code").toString();
                if (code == "200")
                {
                    std::string temp_string = message.toStdString(),sub_str;
                    int fin = temp_string.find("-");
                    first = ++fin;
                    while( temp_string[fin]!= '-')
                    {
                        fin++;
                    }
                    last = --fin;
                    sub_str = temp_string.substr(first , last - first + 1);
                    int count = stoi(sub_str);
                    std::string block = "block ";
                    QString  value, text;
                    for(int i = 0 ; i < count ; i++)
                    {
                        block += (i + '0');
                        value = QString::fromStdString(block);
                        object_mes = temp.value(value).toObject();
                        text = object_mes.value("channel_name").toString();
                        block = "block ";
                        if(contact_send == text)
                        {
                            state=1;
                        }
                    }
                    if(state == 0)
                    {
                        QMessageBox::warning(this ,"Error", "You have not joined the channel yet");
                    }

                }
                if(state==1)
                {
                    QUrl send("http://api.barafardayebehtar.ml:8080/sendmessage"+type_send+"?token="+token+"&dst="+contact_send+"&body=roz khosh");
                    MyThread *thread = new MyThread(send,this);
                    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
                    thread->start();
                    thread->wait();
                    QJsonObject temp  = thread->jason_temp_thread;
                    QString code = temp.value("code").toString();
                    if(code!="200")
                    {
                        state=0;
                        QMessageBox::warning(this ,"Error", "You are not channel`s admin");
                    }
                }

            }
        }
        else
        {
            for(i;i<=i1;i++)
            {
                Sleep(10);
                ui->progressBar->setValue(i);
            }
            Sleep(100);
            if(type_send=="channel")
            {
                for(int i=0;i<channelhas;i++)
                {
                    if(contact_send==channelha[i])
                        state=1;
                }
            }
            if(type_send=="group")
            {
                for(int i=0;i<grouphas;i++)
                {
                    if(contact_send==groupha[i])
                        state=1;
                }
            }
            if(type_send=="user")
            {
                for(int i=0;i<userhas;i++)
                {
                    if(contact_send==userha[i])
                        state=1;
                }
            }
            i1=rand()%20+20+i1;
            for(i;i<=i1;i++)
            {
                Sleep(10);
                ui->progressBar->setValue(i);
            }
            Sleep(50);
            if(state==0)
                QMessageBox::warning(this ,"Error", "This contact was not found to update log out and log in again.");

        }

        if(state==1)
        {
            for( i;i<101;i++)
            {
                Sleep(10);
                ui->progressBar->setValue(i);
            }
            Sleep(400);
            state=0;
            send_p->show();
            emit send_p->starty();
        }
        ui->lineEdit_4->clear();
        ui->progressBar->setValue(0);
    }
    catch (std::exception & e)
        {
            QMessageBox::warning(this , "Error" , e.what());
        }
}


void User_Page::on_User_Page_finished(int result)
{
    if(MyThread::isOnline())
     {
        int i=0;
        int i1;
        i1=rand()%20+20;
        ui->progressBar->show();
        for(i;i<=i1;i++)
        {
            Sleep(5);
            ui->progressBar->setValue(i);
        }
        int channels_number , groups_number , users_number;
        std::string * channels_names;
        std::string * groups_names;
        std::string * users_names;
        QString typy , addressy;
        for (int ori =  0 ; ori < 3 ; ori++)
        {
            if(ori  == 0 )
            {
                typy = "channel";
            }
            else if(ori  == 1)
            {
                typy = "group";
            }
            else if(ori  == 2)
            {
                typy = "user";
            }
            if(MyThread::isOnline())
            {
                addressy = "http://api.barafardayebehtar.ml:8080/get" + typy +"list?token=" +token;
                QUrl send(addressy);
                MyThread *thread = new MyThread(send,this);
                connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
                thread->start();
                thread->wait();

                int first = 0 , last = 0;
                QJsonObject temp  = thread->jason_temp_thread , object_mes;
                QString message = temp.value("message").toString();
                QString code = temp.value("code").toString();
                if (code == "200")
                {
                    std::string temp_string = message.toStdString(),sub_str;
                    int fin = temp_string.find("-");
                    first = ++fin;
                    while( temp_string[fin]!= '-')
                    {
                        fin++;
                    }
                    last = --fin;
                    sub_str = temp_string.substr(first , last - first + 1);
                    int count = stoi(sub_str);
                    std::string block = "block ";
                    QString  value, text;
                    /******/
                    if(ori  == 0 )
                    {
                        if(count != 0)
                        {
                            channels_names = new std::string[count];
                            channels_number = count;
                        }
                        else
                        {
                            channels_number=0;
                            continue;

                        }
                    }
                    else if(ori  == 1)
                    {
                        if(count != 0)
                        {
                            groups_names = new std::string[count];
                            groups_number = count;
                        }
                        else
                        {
                            groups_number=0;
                            continue;

                        }
                    }
                    else if(ori  == 2)
                    {
                        if(count != 0)
                        {
                            users_names =  new std::string[count];
                            users_number = count;
                        }
                        else
                        {
                            users_number=0;
                            continue;

                        }
                    }
                    /******/

                    for(int i = 0 ; i < count ; i++)
                    {
                        block += (i + '0');
                        value = QString::fromStdString(block);
                        //number = i + '0';
                        object_mes = temp.value(value).toObject();
                        if(ori != 2)
                            text = object_mes.value(typy + "_name").toString();
                        else
                            text = object_mes.value("src").toString();

                        /*********/
                        if(ori  == 0 )
                        {
                            channels_names[i] = text.toStdString();
                        }
                        else if(ori  == 1)
                        {
                            groups_names[i] = text.toStdString();
                        }
                        else if(ori  == 2)
                        {
                            users_names[i] = text.toStdString();
                        }
                        /*********/
                        block = "block ";
                    }

                }
            }
        }
        std::string file_path = __FILE__;
        std::string dir_path = file_path.substr(0, file_path.rfind("\\cpp"));
        for (int ori2 = 0 ; ori2 < 3 ; ori2++)
        {
            std::string address , all  , name_file;
            int county_loop = 0;

            if(ori2  == 2)
            {
                address = "Users";
                county_loop = users_number;
            }
            else if(ori2 == 1)
            {
                address = "Groups";
                county_loop = groups_number;
            }
            else if(ori2 == 0)
            {
                address = "Channels";
                county_loop = channels_number;
            }
            for (int jj = 0 ; jj < county_loop ; jj ++)
            {
                if(ori2  == 2)
                {
                    typy = "user";
                    name_file = users_names[jj];
                }
                else if(ori2 == 1)
                {
                    typy = "group";
                    name_file = groups_names[jj];
                }
                else if(ori2 == 0)
                {
                    typy = "channel";
                    name_file = channels_names[jj];

                }
                dir_path = file_path.substr(0, file_path.rfind("\\cpp"));
                dir_path += "\\" + address + "\\" +(name_file) + ".txt";
                remove(dir_path.c_str());
        }
        }
        i1=rand()%20+20+i1;
        for(i;i<=i1;i++)
        {
            Sleep(5);
            ui->progressBar->setValue(i);
        }
        Sleep(20);

         QUrl send("http://api.barafardayebehtar.ml:8080/logout?username=" + username_glob +"&password="+password_glob);
         MyThread *thread = new MyThread(send,this);
         connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
         thread->start();
         thread->wait();
         QJsonObject temp  = thread->jason_temp_thread;
         QString message = temp.value("message").toString();
         QString code = temp.value("code").toString();
         if (code == "200"){
             for( i;i<101;i++)
             {
                 Sleep(5);
                 ui->progressBar->setValue(i);
             }
             QMessageBox::information(this , code , message);
             this->close();
         }
    }
 }
