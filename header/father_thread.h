#ifndef FATHER_THREAD_H
#define FATHER_THREAD_H

#include <QThread>
#include <QObject>

class father_thread : public QThread
{
    Q_OBJECT
public:
    explicit father_thread(QObject *parent = nullptr);
signals:
    void khalife();
};

#endif // FATHER_THREAD_H
