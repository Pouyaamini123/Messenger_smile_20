#ifndef USER_PAGE_H
#define USER_PAGE_H
//#include <QtNetwork/QNetworkConfigurationManager>
#include <QDialog>
#include <QJsonObject>
#include "user_account.h"
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

private:
    int creat;
    int join;
    int list;
    Ui::User_Page *ui;
};

#endif // USER_PAGE_H
