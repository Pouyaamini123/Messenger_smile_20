#include "get_thread.h"

get_thread::get_thread()
{

}

void get_thread::run()
{
    if(MyThread::isOnline())
    {

        QUrl send_2("http://api.barafardayebehtar.ml:8080/get"+type_send+"chats?token="+token+"&dst="+name_send);
        qDebug() << "halghe ... \n";
        MyThread *thread_2 = new MyThread(send_2,this);
        connect(thread_2, SIGNAL(finished()), thread_2, SLOT(deleteLater()));
        thread_2->start();
        thread_2->wait();

        int first = 0 , last = 0;
        QJsonObject temp  = thread_2->jason_temp_thread;
//        qDebug() << temp;
        std::string temp_string  = temp.value("message").toString().toStdString() , sub_str;
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
        if (county != 0 && count == county)
        {
            //;
        }
//        else
//        {
//            county = count;
//        }
        QString message = temp.value("message").toString();
        QString code = temp.value("code").toString();
        if (code == "200")
        {
            std::string temp_block = "block ";
            QString block ;
            QString src ,dst, body_main_message ,date , append_text , temp_mess_get;
            QJsonValue temp_messages;
            for(int i = county ; i < count ; i++)
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
                temp_mess_get = src + " : " + body_main_message + "\n";
                emit khalife(temp_mess_get);
            }
            county = count;
        }
    }
}
