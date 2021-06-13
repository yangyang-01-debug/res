#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>

class MyTimer : public QTimer
{
    Q_OBJECT
public:
    MyTimer(int id,QObject *parent = nullptr);

signals:

public:
    int id = -1;
};

#endif // MYTIMER_H
