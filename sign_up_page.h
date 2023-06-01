#ifndef SIGN_UP_PAGE_H
#define SIGN_UP_PAGE_H


#include <QDialog>

namespace Ui {
class Sign_Up_Page;
}

class Sign_Up_Page : public QDialog
{
    Q_OBJECT

public:
    explicit Sign_Up_Page(QWidget *parent = nullptr);
    ~Sign_Up_Page();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Sign_Up_Page *ui;

};

#endif // SIGN_UP_PAGE_H
