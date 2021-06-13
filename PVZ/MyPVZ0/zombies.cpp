#include "zombies.h"
#include <QDebug>
Zombies::Zombies(int id, QWidget *parent)
{
    this->m_id = id;
    this->m_zombie = new BasicZombies(parent);
    setDefaultBlood();
    this->m_zombie->move(QPoint(2000,-350));
    this->m_zombie->setZombieStyle(NORMAL_ZOMBIE);
    this->setZombiesInfo(DEFAULEINFO);
}

Zombies::~Zombies()
{
    if(this->m_zombie != nullptr){
        delete this->m_zombie;
        this->m_zombie = nullptr;
    }
}

void Zombies::setDefaultBlood()
{
    this->m_blood = this->defaultBlood;
    QString str = zombiehert_;
    this->m_hert = str.toInt();
}

void Zombies::show()
{
    this->m_zombie->show();
}

void Zombies::create(QPoint point)
{
    this->m_zombie->move(point);
    this->show();
    this->setDefaultBlood();
    this->m_is_died = false;
    this->setZombiesInfo(RUNNING);
}

void Zombies::deleted()
{
    this->m_is_died = true;
    this->move(QPoint(2000,-350));
    this->m_col = -1;
    this->m_zombie->stopMovie();
    this->setZombiesInfo(DEFAULEINFO);
}

void Zombies::setCol(int col)
{
    this->m_col = col;
}

void Zombies::move(QPoint point)
{
    this->m_zombie->move(point);
}


void Zombies::setZombiesInfo(ZombieInfo info)
{   //qDebug()<<this->m_zombie->m_zombieInfo<<info;
    if(this->m_zombie->m_zombieInfo == info){
        return;
    }
    /*enum ZombieInfo{
    ATTACKING,0
    DIED,1
    RUNNING,2
    DEFAULEINFO3
};*/
    if(this->m_blood <= 0){
        if(this->m_zombie->m_zombieInfo == DIED){
            return;
        }
        this->m_zombie->setPixMap(":/resources/jspvz/images/zombies/Zombie/ZombieDie.gif");
        //qDebug()<<"start died";
        this->m_zombie->m_zombieInfo = DIED;
        //this->m_col = -1;
//        this->m_zombie->move(QPoint(this->m_zombie->m_label->pos().x() + 2,
//                                    this->m_zombie->m_label->pos().y()));
        this->m_zombie->startMovie();
        return;
    }
    this->m_zombie->m_zombieInfo = info;
    if(this->m_zombie->m_zombieInfo == RUNNING){
        this->m_zombie->setPixMap(":/resources/jspvz/images/zombies/Zombie/Zombie.gif");
        //this->m_zombie->setZombieInfo(info);
        this->m_zombie->startMovie();
        int k = this->m_id % 3;
        this->m_zombie->move(QPoint(this->m_zombie->m_label->pos().x() + k*5,
                                    this->m_zombie->m_label->pos().y()));
        //qDebug()<<"start running";
    }else if (this->m_zombie->m_zombieInfo == ATTACKING) {
        this->m_zombie->setPixMap(":/resources/jspvz/images/zombies/Zombie/ZombieAttack.gif");
        //qDebug()<<"start attack";
//        this->m_zombie->move(QPoint(this->m_zombie->m_label->pos().x() + 2,
//                                    this->m_zombie->m_label->pos().y()));
        this->m_zombie->startMovie();
    }else {

    }
}

void Zombies::setBlood(int blood)
{
    this->defaultBlood = blood;
}

void Zombies::on_timeout()
{
    if(this->m_is_died == true){
        return;
    }
    if(this->m_blood <= 0){
        this->dieCount++;
        this->m_zombie->m_rect.moveTo(QPoint(2000,-350));
        setZombiesInfo(DIED);
        if(this->dieCount % this->dieTimeCount ==0){
            this->dieCount = 0;
            deleted();
            //qDebug()<<"ded";
            return;
        }
    }
    if(this->speedCount >= this->speedTimeCount * 100){
        this->speedCount = 0;
    }
    this->speedCount++;
    if(this->m_zombie->m_zombieInfo == RUNNING){
        if(this->speedCount % this->speedTimeCount == 0){
            this->m_zombie->move(QPoint(this->m_zombie->m_label->pos().x() - this->speed,
                                        this->m_zombie->m_label->pos().y()));
        }
    }
}
