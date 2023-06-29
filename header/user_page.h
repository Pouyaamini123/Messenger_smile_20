#ifndef USER_PAGE_H
#define USER_PAGE_H
//#include <QtNetwork/QNetworkConfigurationManager>
#include <QDialog>
#include <QJsonObject>
#include "send_page.h"
namespace Ui {
class User_Page;
}

class User_Page : public QDialog
{
    Q_OBJECT

public:
    explicit User_Page(QWidget *parent = nullptr);
    ~User_Page();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_14_clicked();
private:
    int creat;
    int join;
    int list;
    int sendd;
    Ui::User_Page *ui;
    send_page * send_p;
};
#endif // USER_PAGE_H
