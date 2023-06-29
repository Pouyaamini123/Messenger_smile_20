#include "..\header\thread_write.h"
#include <fstream>
#include <iostream>
using namespace std;

void thread_write::run()
{
    while(MyThread::isOnline())
     {

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
                        //int count = temp_string[fin] - '0';
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
                                continue;
                        }
                        else if(ori  == 1)
                        {
                            if(count != 0)
                            {
                                groups_names = new std::string[count];
                                groups_number = count;
                            }
                            else
                                continue;
                        }
                        else if(ori  == 2)
                        {
                            if(count != 0)
                            {
                                users_names =  new std::string[count];
                                users_number = count;
                            }
                            else
                                continue;
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
                    //          if (code == "204")
                    //               //QMessageBox::warning(this , code , message);
                    //          if (code == "404")
                    //             // QMessageBox::warning(this , code , message);
                    //          if (code == "401")
                    //             // QMessageBox::warning(this , code , message);

                }
                else
                {
                    // QMessageBox::warning(this , "InterNet Connection " ," You Are Not Connected To Interted");
                }
            }
            /***************************************************************************/
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
                    ofstream test(dir_path);
                    QUrl send_2("http://api.barafardayebehtar.ml:8080/get"+typy+"chats?token="+token+"&dst="+QString::fromStdString(name_file));
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

                    if (code == "200")
                    {

                        std::string temp_block = "block " , filewrite;
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
                            temp_mme.src = src.toStdString() ;
                            temp_mme.body = body_main_message.toStdString();
                            test<<temp_mme.body<<" "<<temp_mme.src<<" ";

                        }
                        //File_ptr.close();
                        test.close();
                    }
                    //         if (code == "401")
                    //             //QMessageBox::warning(this , code , message);
                }
       }
    }
    if(!MyThread::isOnline())
        this->exit();
}
