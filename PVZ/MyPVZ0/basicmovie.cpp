#include "basicmovie.h"
#include <QDebug>

BasicMovie::BasicMovie(QWidget *parent)
{
    this->m_label = new QLabel(parent);
    this->m_movie = nullptr;
    this->m_isBeBoomed = false;
    this->m_rect.moveTo(QPoint(0,0));
    this->m_label->setFixedSize(100,100);
    this->m_rect.setSize(QSize(50,50));
}

BasicMovie::~BasicMovie()
{
    if(this->m_movie != nullptr){
        delete this->m_movie;
        this->m_movie = nullptr;
    }
    if(this->m_label != nullptr){
        delete this->m_label;
        this->m_label = nullptr;
    }
}

void BasicMovie::setFixedSize(const QSize &size)
{
    this->m_label->setFixedSize(size);
}

void BasicMovie::move(const QPoint &point)
{
    this->m_label->move(point);
    this->m_rect.moveCenter(QPoint(this->m_label->pos().x()+ this->m_label->width()/2,
                                   this->m_label->pos().y() + this->m_label->height()/2));
    this->m_point = point;
}

void BasicMovie::startMovie()
{
    if(this->m_movie != nullptr){
        this->m_movie->start();
    }
}

void BasicMovie::stopMovie()
{
    if(this->m_movie != nullptr){
        this->m_movie->stop();
    }
}

void BasicMovie::show()
{
    this->m_label->show();
}

void BasicMovie::hide()
{
    this->m_label->hide();
}


void BasicMovie::setPixmapLabel(const QString &mapPath)
{
    QString str = QString("%1").arg(mapPath);
    if(str.indexOf(".") == -1){
        return;
    }
    QStringList list = str.split(".");
    if(list[1] == "gif"){
        if(this->m_movie == nullptr){
            this->m_movie = new QMovie(mapPath);
        }else {
            delete this->m_movie;
            this->m_movie = nullptr;
            this->m_movie = new QMovie(mapPath);
        }
        QPixmap p;
        p.load(mapPath);
        this->m_label->clear();
        this->m_label->setFixedSize(p.width(),p.height());
        this->m_label->setMovie(this->m_movie);
    }else {
        this->m_label->clear();
        this->m_label->setPixmap(QPixmap(mapPath));
    }
}
