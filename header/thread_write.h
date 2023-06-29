#ifndef THREAD_WRITE_H
#define THREAD_WRITE_H
#include <QThread>
#include "..\header\mythread.h"
#include "..\header\user_account.h"
#include <iostream>
#include <QFile>
class thread_write : public QThread
{
public:
    void run() override;
};
#endif // THREAD_WRITE_H
