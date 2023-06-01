#include "sign_up_page.h"
#include "ui_sign_up_page.h"

Sign_Up_Page::Sign_Up_Page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sign_Up_Page)
{
    ui->setupUi(this);
}

Sign_Up_Page::~Sign_Up_Page()
{
    delete ui;
}

void Sign_Up_Page::on_pushButton_2_clicked()
{
    ui->lineEdit_2->setText("");
    ui->lineEdit->setText("");
    this->close();

}

void Sign_Up_Page::on_pushButton_3_clicked()
{

    ui->lineEdit_2->setText("");
    ui->lineEdit->setText("");
    this->close();
}



