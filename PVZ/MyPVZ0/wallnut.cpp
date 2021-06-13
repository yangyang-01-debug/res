#include "wallnut.h"
int  WallNut::m_cost = 125;
WallNut::WallNut(QWidget *parent)
{
    m_plant = new BasicPlants(parent);
    m_plant->setPlantStyle(nut);
    setDefaultBlood();
    move(QPoint(0,-300));
}

WallNut::~WallNut()
{
    if(m_plant != nullptr){
        delete m_plant;
        m_plant = nullptr;
    }
}

void WallNut::show()
{
    m_plant->show();
}

void WallNut::setCol_Id(int col, int id)
{
    this->m_col = col;
    this->m_id = id;
}

void WallNut::move(QPoint point)
{
    m_plant->move(point);
}

void WallNut::create(QPoint point)
{
    this->m_is_died = false;
    setWallNutStyle(HEALTH);
    setDefaultBlood();
    move(point);
    show();
}

void WallNut::setDefaultBlood()
{
    this->m_blood = defaultblood;
}

void WallNut::setBlood(int blood)
{
    defaultblood = blood;
}

void WallNut::deleted()
{
    this->m_is_died = true;
    move(QPoint(0,-300));
}

void WallNut::subBlood(int hert)
{
    this->m_blood -= (hert - hujia);
}

void WallNut::setWallNutStyle(WallNutBlood style)
{
    if(this->style == style){
        return;
    }
    this->style = style;
    switch (style) {
    case HEALTH:{
        this->m_plant->setPixmapLabel(":/resources/jspvz/images/plants/WallNut/healthNull.gif");
        this->m_plant->startMovie();
        break;
    }
    case NOTHEALTH:{
        this->m_plant->setPixmapLabel(":/resources/jspvz/images/plants/WallNut/nothealthNull.gif");
        this->m_plant->startMovie();
        break;
    }
    case BEDIED:{
        this->m_plant->setPixmapLabel(":/resources/jspvz/images/plants/WallNut/bediedNull.gif");
        this->m_plant->startMovie();
        break;
    }
    default:
        break;
    }
}

void WallNut::on_timeout()
{
    if(this->m_is_died == true){
        return;
    }
    if(this->m_blood <= 0){
        deleted();
    }

    if(defaultblood/3<this->m_blood &&  this->m_blood<= defaultblood/3*2){
        setWallNutStyle(NOTHEALTH);
    }else if (this->m_blood <= defaultblood/3) {
        setWallNutStyle(BEDIED);
    }else {
        setWallNutStyle(HEALTH);
    }

}
