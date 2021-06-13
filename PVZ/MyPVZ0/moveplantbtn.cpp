#include "moveplantbtn.h"
#include <QPixmap>
#include <QDebug>
#include "chooseplantstitllbar.h"
MovePlantBtn::MovePlantBtn(QWidget *parent) : BasicPlantBtn(parent)
{}

MovePlantBtn::MovePlantBtn(QString name, const QString &mapPath, QWidget *parent)
    : BasicPlantBtn(name,mapPath,parent)
{
    this->m_moveLabel = new Label(parent);
    this->m_moveLabel->setPixmapLabel(mapPath);
    this->m_moveLabel->setFixedSizeLabel(QSize(this->width(),this->height()));
    this->m_moveLabel->hide();
    m_name = name;
}

void MovePlantBtn::setTextLabel(QString text, QWidget *parent)
{
    this->m_text = new QLabel(parent);
    QFont f;
    f.setPointSize(9);
    this->m_text->setFont(f);
    this->m_text->setMouseTracking(true);
    this->m_text->setStyleSheet("background-color:rgb(0,255,0)");
    this->m_text->setText(text);
    this->m_text->setFixedWidth(this->width());
    this->m_text->move(this->pos().x(),this->pos().y() + this->height()-5);
    this->m_text->show();
}

MovePlantBtn::~MovePlantBtn()
{
    if(m_text != nullptr){
        delete m_text;
        m_text = nullptr;
    }
}

void MovePlantBtn::mouseDoubleClickEvent(QMouseEvent *)
{

}

void MovePlantBtn::mouseMoveEvent(QMouseEvent *e)
{
    //qDebug()<<"eve";
    if(this->m_isPressed){
        //qDebug()<<"move";
        this->m_moveLabel->show();
        this->m_moveLabel->move(e->pos()- this->m_pressPoint +this->pos());
    }else {
//       this->m_moveLabel->hide();
//        if(this->m_isClicked){
//            this->m_moveLabel->show();
//            this->m_moveLabel->move(e->pos()- this->m_pressPoint +this->pos());
//        }else {
//            this->m_moveLabel->hide();
//        }
    } 
}

void MovePlantBtn::mouseReleaseEvent(QMouseEvent *e)
{
    this->m_is_press = false;
    m_releasePoint  = e->pos() + this->pos();
    this->m_isPressed = false;
    this->m_moveLabel->hide();
    //this->m_label->show();
    this->m_label->hide();
    ChoosePlantsTitllBar::plantName = this->m_name;
    emit signalMousePoint(m_releasePoint);
}

void MovePlantBtn::mousePressEvent(QMouseEvent *e)
{
    this->m_isbeChoosed = true;
    this->m_isPressed = true;
    this->m_pressPoint = e->pos();
    this->m_label->show();
    this->m_is_press = true;
}

//void MovePlantBtn::mousePressEvent(QMouseEvent *e)
//{
//    this->m_pressPoint = e->pos();
//    //this->m_size = this->size();
//    this->m_isPressed = true;
//    if(this->m_isbeChoosed == true){
//        this->m_isbeChoosed = false;
//        //qDebug()<<"hide";
//        this->m_label->hide();
//    }
//}
