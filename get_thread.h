#ifndef GET_THREAD_H
#define GET_THREAD_H
#include "jjthread.h"
#include "mythread.h"
#include <QThread>

class get_thread : public jjthread
{
public:
    explicit get_thread();
    void run() override;
    int h=0;
};

#endif // GET_THREAD_H
