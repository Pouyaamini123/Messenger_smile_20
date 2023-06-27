#ifndef SEND_PAGE_H
#define SEND_PAGE_H
#include "user_account.h"
#include "get_thread.h"

#include <QDialog>
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
    void put(QString);
        void start_thread();
private slots:
    void on_pushButton_clicked();

private:
    get_thread * thread_sec;
    Ui::send_page *ui;
};

#endif // SEND_PAGE_H
