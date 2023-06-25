#include "send_page.h"
#include "ui_send_page.h"
#include "user_account.h"
send_page::send_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::send_page)
{
    ui->setupUi(this);
}

send_page::~send_page()
{
    delete ui;
}
