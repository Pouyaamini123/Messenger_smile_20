#include "..\header\get_thread.h"

get_thread::get_thread()
{

}

void get_thread::run()
{
    while(true)
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

        if(h!=count)
        {
            h=count;
            emit khalife();
        }
    }
}
