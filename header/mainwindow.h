#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "mythread.h"
#include <QMainWindow>
#include <QMessageBox>
#include "sign_up_page.h"
#include "user_page.h"
#include "user_account.h"
#include "..\header\thread_write.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static void move_back();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void write_in_files();
signals:
    void khelafat();
private:
    thread_write * ptr;
    Ui::MainWindow *ui;
    Sign_Up_Page *sign_page;
    User_Page *user_page;

};
#endif // MAINWINDOW_H
