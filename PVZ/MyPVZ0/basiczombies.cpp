#include "basiczombies.h"
#include <QDebug>
BasicZombies::BasicZombies(QWidget *parent) : BasicMovie(parent)
{

    this->m_zombieInfo = DEFAULEINFO;
    this->m_rect.moveTo(QPoint(this->m_label->pos().x() + 70,this->m_label->pos().y()));
}

BasicZombies::~BasicZombies()
{}

void BasicZombies::move(const QPoint &point)
{
    this->m_label->move(point);
    this->m_rect.moveCenter(QPoint(this->m_label->pos().x()+20 + this->m_label->width()/2,
                                   this->m_label->pos().y() + this->m_label->height()/2));
    this->m_point = point;
}

void BasicZombies::setZombieStyle(ZombieStyle style)
{
    this->m_zombieStyle = style;
    switch (style) {
    case CONEHEAD_ZOMBIE:{
        this->setPixmapLabel(QString(":/resources/jspvz/images/zombies/ConeheadZombie/ConeheadZombie.gif"));
        break;
    }
    case NORMAL_ZOMBIE:{
        this->setPixmapLabel(QString(":/resources/jspvz/images/zombies/Zombie/Zombie.gif"));
        break;
    }
    default:{
        this->setPixmapLabel(QString(":/resources/jspvz/images/zombies/Zombie/Zombie.gif"));
        break;
    }
    }
}

void BasicZombies::setFixedSize(QSize size)
{
    this->m_label->setFixedSize(size);
    this->m_rect.setSize(size);
}

void BasicZombies::setZombieInfo(ZombieInfo zombieInfo)
{
   this->m_zombieInfo = zombieInfo;
}

void BasicZombies::setPixMap(const QString &map)
{
    this->setPixmapLabel(map);
}
