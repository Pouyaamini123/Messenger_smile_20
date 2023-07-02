#ifndef GET_THREAD_H
#define GET_THREAD_H
#include "father_thread.h"
#include "mythread.h"
#include <QThread>

class get_thread : public father_thread
{
public:
    explicit get_thread();
    void run() override;
    int message_number = 0;
};

#endif // GET_THREAD_H
