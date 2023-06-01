#include "user_page.h"
#include "ui_user_page.h"

User_Page::User_Page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User_Page)
{
    ui->setupUi(this);
}

User_Page::~User_Page()
{
    delete ui;
}
