#include "basicpbs.h"
#include <QDebug>
//int cout =0;
//int couttime = 100;
BasicPbs::BasicPbs(QWidget *parent) : BasicMovie(parent)
{
//    this->m_label = new QLabel(parent);
//    this->m_movie = nullptr;
//    this->m_isBeBoomed = false;
//    this->m_rect.setTopLeft(QPoint(0,0));
//    this->m_label->setFixedSize(100,100);
//    this->m_rect.setSize(QSize(100,100));
    this->m_rect.setSize(QSize(60,50));
    this->m_rect.moveCenter(QPoint(this->m_label->pos().x() + this->m_label->width()/2 - this->m_rect.width()/2+20,
                                   this->m_label->pos().y() + this->m_label->height()/2 - this->m_rect.height() /2));
    this->is_shooted = false;
    this->m_len = 0;
//    this->m_timer = new QTimer();
//    connect(this->m_timer,&QTimer::timeout,this,&BasicPbs::on_timeout);
    //this->m_point = QPoint(0,0);
    setPbsType(NORMAL_TYPE);
}

void BasicPbs::setPbsType(PbsType type)
{/*
    NORMAL = ":/resources/jspvz/images/plants/PBS/PBnormal.png",
    Fire = ":/resources/jspvz/images/plants/PBS/PBfire.gif",
    ICE = ":/resources/jspvz/images/plants/PBS/PBice.gif"
*/
    this->m_Pbstype = type;
    switch (type) {
    case NORMAL_TYPE:{
        setPixmapLabel(QString(":/resources/jspvz/images/plants/PBS/PBnormal.png"));
        this->m_hert = this->m_basichert;
        break;
    }
    case FIRE_TYPE:{
        setPixmapLabel(QString(":/resources/jspvz/images/plants/PBS/PBfire.gif"));
        this->m_hert = this->m_basichert * 4;
        break;
    }
    case ICE_TYPE:{
        setPixmapLabel(QString(":/resources/jspvz/images/plants/PBS/PBice.gif"));
        this->m_hert = this->m_basichert * 2;
        break;
    }
    default:
        setPixmapLabel(QString(":/resources/jspvz/images/plants/PBS/PBnormal.png"));
         this->m_Pbstype = NORMAL_TYPE;
        this->m_hert = this->m_basichert;
        break;
    }
}

void BasicPbs::move(const QPoint &point)
{
   // if(cout%couttime==0){
        this->m_len += this->m_speed;
   // }
//    if(cout>=couttime*100){
//        cout = 1;
//    }
    this->m_label->move(point);
    //this->m_rect.moveTo(QPoint(this->m_label->pos().x(),this->m_label->pos().y()));
    this->m_rect.moveCenter(QPoint(this->m_label->pos().x() + this->m_label->width()/2,
                                   this->m_label->pos().y() + this->m_label->height()/2));
    //this->m_leftTop = this->m_label->pos();
}

//void BasicPbs::setPixmapLabel(const QString &mapPath)
//{
//    QString str = QString("%1").arg(mapPath);
//    if(str.indexOf(".") == -1){
//        return;
//    }
//    QStringList list = str.split(".");
//    if(list[1] == "gif"){
//        if(this->m_movie == nullptr){
//            this->m_movie = new QMovie(mapPath);
//        }else {
//            delete this->m_movie;
//            this->m_movie = nullptr;
//            this->m_movie = new QMovie(mapPath);
//        }
//        this->m_label->clear();
//        this->m_label->setMovie(this->m_movie);
//    }else {
//        this->m_label->clear();
//        this->m_label->setPixmap(QPixmap(mapPath));
//    }
//    qDebug()<<list[1];
//}

//void BasicPbs::setFixedSize(const QSize &size)
//{
//    this->m_label->setFixedSize(size);
//    this->m_rect.setSize(size);
//}

//void BasicPbs::move(const QPoint &point)
//{
//    this->m_label->move(point);
//    this->m_rect.moveTopLeft(point);
//}

//void BasicPbs::startMovie()
//{
//    if(this->m_movie != nullptr){
//        this->m_movie->start();
//    }
//}

//void BasicPbs::stopMovie()
//{
//    if(this->m_movie != nullptr){
//        this->m_movie->stop();
//    }
//}

//void BasicPbs::show()
//{
//    this->m_label->show();
//}

BasicPbs::~BasicPbs()
{
//    if(this->m_timer != nullptr){
//        delete this->m_timer;
//        this->m_timer = nullptr;
//    }
//    if(this->m_movie != nullptr){
//        delete this->m_movie;
//        this->m_movie = nullptr;
//    }
//    if(this->m_label != nullptr){
//        delete this->m_label;
//        this->m_label = nullptr;
    //    }
}


void BasicPbs::on_timeout()
{
//    if(this->is_shooted == false){
//        return;
//    }
//    this->move(QPoint(this->m_label->pos().x() + this->m_speed,this->m_label->pos().y()));
//    if(this->m_label->pos().x() > 500){
//        this->hide();
//        this->is_shooted = false;
//    }
}

