#ifndef THREAD10_H
#define THREAD10_H

#include "father_thread.h"
#include "mythread.h"
#include <QThread>

class thread10 : public father_thread
{
public:
    explicit thread10();
    void run() override;
};
#endif // THREAD10_H
