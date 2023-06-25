#ifndef SEND_PAGE_H
#define SEND_PAGE_H

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

private:

    Ui::send_page *ui;
};

#endif // SEND_PAGE_H
