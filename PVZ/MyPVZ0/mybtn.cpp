#include "mybtn.h"
#include <QDebug>
#include <QSizePolicy>
MyBtn::MyBtn()
{
    this->m_button = nullptr;
    this->m_label = nullptr;
}

MyBtn::MyBtn(QWidget *parent)
{
    this->m_button = new Button(parent);
    this->m_label = new Label(parent);
    this->m_label->setMouseTracking(true);
    this->m_label->hide();
    connect(this->m_button,&Button::clicked,this,&MyBtn::onButtonClicked);
    connect(this->m_button,&Button::pressed,this,&MyBtn::onButtonPressed);
    connect(this->m_button,&Button::released,this,&MyBtn::onButtonReleased);
}

MyBtn::~MyBtn()
{
    if(this->m_button != nullptr){
        delete this->m_button;
        this->m_button = nullptr;
    }
}

void MyBtn::setPixMapBtn(const QString &path)
{
    this->m_button->setPixmapBtn(path);
    this->m_point = this->m_button->pos();
    this->m_label->setPixmapLabel(path);
}

void MyBtn::setFixedSizeBtn(const QSize &size)
{
    this->m_button->setFixedSize(size);
    this->m_label->setFixedSizeLabel(QSize(size.width(),size.height()+10));
}

void MyBtn::setText(const QString &text, const QFont &font)
{
    this->m_button->setTextBtn(text,font);
    this->m_label->setTextLabel(text,font);
}


void MyBtn::setSizePolicy(const SizePolicy &Hpolicy, const SizePolicy &Vpolicy)
{
    QSizePolicy policy;
    if(Hpolicy == Expanding){
        policy.setHorizontalPolicy(QSizePolicy::Expanding);
    }else if (Hpolicy == Fixed) {
        policy.setHorizontalPolicy(QSizePolicy::Fixed);
    }
    if(Vpolicy == Expanding){
        policy.setVerticalPolicy(QSizePolicy::Expanding);
    }else if (Vpolicy == Fixed) {
        policy.setVerticalPolicy(QSizePolicy::Fixed);
    }
    this->m_button->setSizePolicy(policy);
}

void MyBtn::move(const QPoint &point)
{
    this->m_button->move(point);
    this->m_label->move(point);
    this->m_point = point;
}

void MyBtn::show()
{
    this->m_button->show();
}

int MyBtn::getWidth()
{
    return this->m_button->width();
}

int MyBtn::getHeigth()
{
    return this->m_button->height();
}

Button *MyBtn::getButton() const
{
    return this->m_button;
}

void MyBtn::onButtonClicked()
{
    emit this->clicked();
    emit this->btnclicked(this->objectName());
    //qDebug()<<"clicked";
}

void MyBtn::onButtonPressed()
{
    emit this->pressed();
    //qDebug()<<"pressed";
    //this->m_button->setVisible(false);
    this->m_label->show();
}

void MyBtn::onButtonReleased()
{
    emit this->released();
    //qDebug()<<"released";
    this->m_label->close();
    //this->m_button->show();
}
