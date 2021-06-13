#include "basicplantsBtn.h"
#include <QDebug>
BasicPlantBtn::BasicPlantBtn(QWidget *parent) : QPushButton(parent)
{
    this->m_label = new Label(this);
    this->m_label->move(QPoint(0,0));
    this->m_label->setMouseTracking(true);
    this->m_isbeChoosed = false;
    this->m_isPressed = false;
    this->m_isClicked = false;
    this->m_label->hide();
    this->setSize(QSize(70,70));
}

BasicPlantBtn::BasicPlantBtn(QString name, const QString &mapPath, QWidget *parent) : QPushButton(parent)
{
    this->m_plantName = name;
    this->m_map.load(mapPath);
    this->m_isPressed = false;
    this->m_isClicked = false;
    this->m_label = new Label(this);
    this->m_label->setPixmapLabel(QString(BLACK_IMAGE));
    this->m_label->move(QPoint(0,0));
    this->m_label->setMouseTracking(true);
    this->m_isbeChoosed = false;
    this->m_label->hide();
    this->setSize(QSize(70,70));
}

void BasicPlantBtn::setPixMap(const QString &mapPath)
{
    this->m_map.load(mapPath);
    this->m_label->setPixmapLabel(QString(BLACK_IMAGE));
    this->update();
}

void BasicPlantBtn::setSize(const QSize &size)
{
    this->m_label->setFixedSizeLabel(size);
    this->setFixedSize(size);
    this->update();
}

BasicPlantBtn::~BasicPlantBtn()
{
    if(this->m_label != nullptr){
        delete this->m_label;
        this->m_label =nullptr;
    }
}

bool BasicPlantBtn::is_Choosed()
{
    return this->m_isbeChoosed;
}

void BasicPlantBtn::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.drawPixmap(0,0,this->width(),this->height(),QPixmap(CHOOSE_IMAGE));
    paint.drawPixmap(5,5,this->width()-10,this->height()-10,this->m_map);
}

void BasicPlantBtn::mouseMoveEvent(QMouseEvent *)
{

}


void BasicPlantBtn::mouseDoubleClickEvent(QMouseEvent *)
{
    this->m_isbeChoosed = true;
    this->m_label->show();
   // qDebug()<<"double";
}

void BasicPlantBtn::mousePressEvent(QMouseEvent *e)
{
    this->m_isPressed = true;
    this->m_pressPoint = e->pos();
    //this->m_size = this->size();
    this->m_isPressed = true;
    if(this->m_isbeChoosed == true){
        this->m_isbeChoosed = false;
        //qDebug()<<"hide";
        this->m_label->hide();
    }
    //qDebug()<<"press";
}

void BasicPlantBtn::mouseReleaseEvent(QMouseEvent *)
{
//qDebug()<<"release";
    if(this->m_isPressed){
        if(this->m_isClicked == true){
            this->m_isClicked = false;
        }else {
            this->m_isClicked = true;
        }
    }
    this->m_isPressed = false;

}
