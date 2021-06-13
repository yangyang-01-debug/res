#include "label.h"
#include <QPainter>
Label::Label(QWidget *parent) : QLabel(parent)
{
    this->setMouseTracking(true);
    this->m_text = "";
    this->m_rect.setTopLeft(QPoint(0,0));
    this->m_p = QPoint(0,0);
}

Label::~Label()
{

}

void Label::setCol_Id(int col, int id)
{
    this->m_col = col;
    this->m_id = id;
}

void Label::moveLabel(QPoint point)
{
    this->move(point);
    this->m_rect.moveTo(point);
}

void Label::setTextLabel(const QString &text, const QFont &font)
{
    this->m_font = font;
    this->m_text = text;
    this->update();
}

void Label::setPixmapLabel(const QString &map)
{
    this->m_map.load(map);
    this->update();
}

void Label::setFixedSizeLabel(const QSize &size)
{
    this->setFixedSize(size);
    this->m_rect.setSize(size);
    this->update();
}

void Label::setDrawPoint(const QPoint &p)
{
    this->m_p = p;
}

void Label::enterEvent(QEvent *)
{
    //emit signalEnterLabel(QPoint(this->m_col,this->m_id));
    emit releasedLabel();
}

//void Label::mousePressEvent(QMouseEvent *)
//{
//    emit
//}

void Label::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(this->m_p.x(),this->m_p.y(),this->width(),this->height(),this->m_map);

    //painter.drawRect(this->m_rect);

    if(this->m_text != ""){
        painter.setFont(this->m_font);
        painter.drawText(35,35,this->m_text);
    }
}

void Label::mouseReleaseEvent(QMouseEvent *)
{
    emit releasedLabel();
}
