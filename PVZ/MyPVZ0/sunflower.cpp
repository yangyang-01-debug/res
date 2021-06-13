#include "sunflower.h"
#include <QDebug>
int sunCount = 0;
int sunCount_time = 1200;
//int sunoverCount_time = 800;
//int sunoverCount =0;
int moveCount = 10;
int SunFlower::m_cost = 50;
int SunFlower::produced = 25;
int SunFlower::timerid = 0;
SunFlower::SunFlower(int id, QWidget *parent)
{
    this->m_plantid = id;
    this->m_sunMovie = new QMovie(QString("%1").arg(SUN_PATH));
    this->m_plant = new BasicPlants(parent);
    this->m_plant->setFixedSize(QSize(100,100));
    this->m_plant->setPlantStyle(sunflower);
    this->m_plant->startMovie();
    this->m_timer = new MyTimer(timerid);
    timerid++;
    for(int i=0; i < SUNNUM; i++){
        this->m_sunlabels[i] = new SunLabel(parent);
        connect(this->m_sunlabels[i],&SunLabel::clicked,this,&SunFlower::onSunClicked);
        this->m_sunlabels[i]->setFixedSize(76,75);
        this->m_sunlabels[i]->move(0,0);
        this->m_sunlabels[i]->setMovie(this->m_sunMovie);
        m_sunMovie->start();
    }
    m_moveSun = new SunLabel(parent);
    m_moveSun->setFixedSize(47,47);
    m_moveSun->move(-100,-300);
    m_moveSun->setMovie(this->m_sunMovie);
    connect(this->m_timer,&QTimer::timeout,this,&SunFlower::on_timeout);
    m_timer->start(10);
    setDefaultBlood();
}

SunFlower::~SunFlower()
{
//    delete m_timer;
//    m_timer = nullptr;
     sunCount = 0;
     sunCount_time = 1200;
    //int sunoverCount_time = 800;
    //int sunoverCount =0;
     moveCount = 10;
    m_cost = 50;
    produced = 25;
    timerid = 0;
    if(m_sunMovie != nullptr){
        delete m_sunMovie;
        m_sunMovie = nullptr;
    }
    if(m_moveSun != nullptr){
        delete m_moveSun;
        m_moveSun = nullptr;
    }
    if(m_timer != nullptr){
        delete m_timer;
        m_timer = nullptr;
    }
    if(m_plant != nullptr){
        delete m_plant;
        m_plant = nullptr;
    }
    for(int i=0; i < SUNNUM; i++){
        if(m_sunlabels[i]!=nullptr){
            this->m_sunlabels[i]->move(-100,-100);
            delete this->m_sunlabels[i];
            this->m_sunlabels[i] = nullptr;
        }
    }
}

void SunFlower::show()
{
    this->m_plant->show();
}

void SunFlower::setCol_Id(int col, int id)
{
    this->m_col = col;
    this->m_id = id;
}

void SunFlower::move(QPoint point)
{
    this->m_plant->move(point);
}

void SunFlower::moveToHide(QPoint point)
{//10,10  point x,y  (y-10)/(x-10)
    if(point.x() == 0){
        point.setX(1);
    }
    int k = (point.y())/(point.x());
    if(k==0)k=1;
    m_moveSun->move(point.x() - moveCount,point.y() - moveCount*k);
    m_moveSun->show();
}

void SunFlower::create(QPoint point)
{
    m_plant->move(point);
    setDefaultBlood();
    this->m_is_died = false;
    //this->m_timer->start(10);
}

void SunFlower::setDefaultBlood()
{
    this->m_blood = defaultblood;
}

void SunFlower::setBlood(int blood)
{
    this->defaultblood = blood;
}

void SunFlower::deleted()
{
    //m_timer->stop();

    for(int i=0;i<SUNNUM;i++){
        this->m_sunlabels[i]->hide();
        this->m_sunlabels[i]->move(-100,-100);
    }
    this->m_is_died = true;
    this->move(QPoint(-100,-100));
    this->m_col = -1;
    this->m_id = -1;
}

void SunFlower::subBlood(int hert)
{
    this->m_blood -= hert;
}

void SunFlower::on_timeout()
{
    QObject *o = this->sender();
    MyTimer *s = qobject_cast<MyTimer*>(o);
    if(s == nullptr){
        return;
    }
    if(s->id != this->m_timer->id){
        return;
    }

    if(isMoveing == true){
        if(l != nullptr){
            if(m_moveSun->pos().x() <= 10 && m_moveSun->pos().y() <= 10){
                isMoveing = false;
                m_moveSun->move(-100,-100);
            }else{
//                qDebug()<<"move";
                moveToHide(m_moveSun->pos());
            }
        }
    }

    if(this->m_is_died == true){
        //m_moveSun
        return;
    }
    if(this->m_blood <= 0){
        deleted();
    }
    if(sunCount >= sunCount_time *100){
        sunCount = 0;
    }
    if(sunCount%sunCount_time ==0){
        //..getSun
        for(int i=0;i < SUNNUM;i++){
            if(this->m_sunlabels[i]->m_is_on == false){
                this->m_sunlabels[i]->m_is_on = true;
                this->m_sunlabels[i]->show();
                this->m_sunlabels[i]->move(this->m_plant->m_label->pos() + QPoint(30-i*20,20));
                //m_moveSun->move(this->m_sunlabels[i]->pos());
                break;
            }
        }
    }
//    for(int i=0;i < SUNNUM;i++){
//        if(this->m_sunlabels[i]->m_is_on == true){
//            sunoverCount++;
//            if(sunoverCount%sunoverCount_time ==0){
//                this->m_sunlabels[i]->m_is_on = false;
//                this->m_sunlabels[i]->move(-100,-100);
//                //moveToHide(m_moveSun->pos());
//            }
//            break;
//        }
//    }
    sunCount++;

}

void SunFlower::onSunClicked()
{
    //qDebug()<<"clicked";
    obj = this->sender();
    l = qobject_cast<SunLabel*>(obj);
    if(l == nullptr){
        return;
    }
    m_moveSun->move(l->pos());
    l->move(-100,-100);
    l->m_is_on = false;
    isMoveing = true;
    emit getSunNum();
}
