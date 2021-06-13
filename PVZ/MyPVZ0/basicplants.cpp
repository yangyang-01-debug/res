#include "basicplants.h"
#include <QDebug>
BasicPlants::BasicPlants(QWidget *parent) :BasicMovie(parent)
{}

BasicPlants::~BasicPlants()
{}

void BasicPlants::move(const QPoint &point)
{
    this->m_label->move(point);
    this->m_rect.moveCenter(QPoint(this->m_label->pos().x()+ this->m_label->width()/2-5,
                                   this->m_label->pos().y() + this->m_label->height()/2));
    this->m_point = point;
}

void BasicPlants::setPlantStyle(PlantStyle style)
{
    //qDebug()<<"style";
    switch (style) {
    case shooter:{
        this->setPixmapLabel(QString(":/resources/jspvz/images/plants/Peashooter/Peashooter.gif"));
        break;
    }
    case nut:{
        this->setPixmapLabel(QString(":/resources/jspvz/images/plants/WallNut/WallNut.gif"));
        break;
    }
    case tallnut:{
        this->setPixmapLabel(QString(":/resources/jspvz/images/plants/TallNut/TallNut.gif"));
        break;
    }
    case sunflower:{
        this->setPixmapLabel(QString(":/resources/jspvz/images/plants/SunFlower/SunFlower1.gif"));
        break;
    }
    default:
        this->setPixmapLabel(QString(""));
        break;
    }

}
