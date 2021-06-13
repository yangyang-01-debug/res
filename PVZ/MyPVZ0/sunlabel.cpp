#include "sunlabel.h"

SunLabel::SunLabel(QWidget *parent) : QLabel(parent){}

void SunLabel::mousePressEvent(QMouseEvent *)
{
    //emit this->clicked();
}

void SunLabel::mouseReleaseEvent(QMouseEvent *)
{
    emit this->clicked();
}
