#include "mytimer.h"

MyTimer::MyTimer(int id, QObject *parent) : QTimer(parent)
{
this->id = id;
}
