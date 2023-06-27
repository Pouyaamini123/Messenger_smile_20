#ifndef JJTHREAD_H
#define JJTHREAD_H

#include <QThread>
#include <QObject>

class jjthread : public QThread
{
    Q_OBJECT
public:
    explicit jjthread(QObject *parent = nullptr);
signals:
    void khalife();
};

#endif // JJTHREAD_H
