#ifndef SEND_PAGE_H
#define SEND_PAGE_H
#include "user_account.h"
#include "get_thread.h"
#include <fstream>
#include <QDialog>
#include<fstream>
namespace Ui {
class send_page;
}

class send_page : public QDialog
{
    Q_OBJECT

public:
    explicit send_page(QWidget *parent = nullptr);
    ~send_page();

signals:
    void starty();
public slots:
    void put();
//    void write_in_file();
    void start_thread();
private slots:
    void on_pushButton_clicked();
    void on_send_page_finished(int result);

private:
    get_thread * thread_sec;
    Ui::send_page *ui;
};
struct last
{
    QString sr;
    QString bo;
};


#endif // SEND_PAGE_H
