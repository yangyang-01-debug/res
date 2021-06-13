#include "button.h"
#include <QPainter>
Button::Button(QWidget *parent) : QPushButton(parent)
{
    this->m_text = "";
}

Button::~Button()
{}

void Button::setPixmapBtn(const QString &path)
{
    this->m_map.load(path);
    this->setFixedSize(this->m_map.size());
    update();
}

void Button::setTextBtn(const QString &text, const QFont &font)
{
    this->m_font = font;
    this->m_text = text;
    update();
}

void Button::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),this->m_map);

    if(this->m_text != ""){
        painter.setFont(this->m_font);
        painter.drawText(35,30,this->m_text);
    }
}
