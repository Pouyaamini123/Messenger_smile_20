#ifndef USER_PAGE_H
#define USER_PAGE_H

#include <QDialog>

namespace Ui {
class User_Page;
}

class User_Page : public QDialog
{
    Q_OBJECT

public:
    explicit User_Page(QWidget *parent = nullptr);
    ~User_Page();

private:
    Ui::User_Page *ui;
};

#endif // USER_PAGE_H
