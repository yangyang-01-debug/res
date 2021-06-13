#include "chooseplantstitllbar.h"
#include <QDebug>
int count = 0;
int start_time = 100;
int m_start = 0;
int ChoosePlantsTitllBar::m_plants_num = 1;
QString ChoosePlantsTitllBar::plantName = "";
ChoosePlantsTitllBar::ChoosePlantsTitllBar(QWidget *parent) : QWidget(parent)
{
    p = parent;
//    m_playerSc = new MediaPlayer();
//    connect(this,&ChoosePlantsTitllBar::doRun,m_playerSc,&MediaPlayer::run);
//    thread = new QThread();
//    m_playerSc->moveToThread(thread);
//    thread->start();
//    this->m_playerSc = new QMediaPlayer(this);
//    QUrl url(QString("qrc%1").arg(ATTACKPath));
//    this->m_playerSc->setMedia(url);
    for(int i=0;i<5;i++){
        for(int j=0;j<9;j++){
            m_labels[i][j] = new Label(parent);
            m_labels[i][j]->hide();
            m_labels[i][j]->setCol_Id(i,j);
            m_labels[i][j]->setFixedSizeLabel(QSize(170,170));
            m_labels[i][j]->moveLabel(QPoint(171*j + 290,171*i+100 + i*10));
            m_labels[i][j]->setPixmapLabel(":/resources/jspvz/black2.png");
            //m_labels[i][j]->show();
            //connect(m_labels[i][j],SIGNAL(releasedLabel()),this,SLOT(on_EnterLabel()));
        }
    }
    m_cintor = new ScreenControler(parent);
    m_cintor->startTime();
    connect(m_cintor,&ScreenControler::attackZombie,this,&ChoosePlantsTitllBar::onattackPlay);
    m_shooterBtn = new MovePlantBtn("shooter",":/resources/jspvz/images/plants/Peashooter/0.png",parent);
    connect(m_shooterBtn,SIGNAL(signalMousePoint(QPoint)),this,SLOT(on_shooterBtnRelease(QPoint)));
    m_shooterBtn->move(150,700);
    m_shooterBtn->setTextLabel(QString("   %1").arg(Shooters::m_cost),parent);
    m_sunflowerBtn = new MovePlantBtn("sunflower",":/resources/jspvz/images/plants/SunFlower/0.png",parent);
    connect(m_sunflowerBtn,SIGNAL(signalMousePoint(QPoint)),this,SLOT(on_shooterBtnRelease(QPoint)));
    m_sunflowerBtn->move(150,600);
    m_sunflowerBtn->setTextLabel(QString("   %1").arg(SunFlower::m_cost),parent);
    m_wallnutBtn = new MovePlantBtn("wallnut",":/resources/jspvz/images/plants/WallNut/0.png",parent);
    connect(m_wallnutBtn,SIGNAL(signalMousePoint(QPoint)),this,SLOT(on_shooterBtnRelease(QPoint)));
    m_wallnutBtn->move(150,500);
    m_wallnutBtn->setTextLabel(QString("   %1").arg(WallNut::m_cost),parent);

    shootlabel = new Label(parent);
    shootlabel->move(m_shooterBtn->pos());
    shootlabel->setFixedSizeLabel(QSize(70,80));
    shootlabel->setPixmapLabel(":/resources/jspvz/black2.png");
    shootlabel->setMouseTracking(false);

    sunflowerLabel = new Label(parent);
    sunflowerLabel->move(m_sunflowerBtn->pos());
    sunflowerLabel->setFixedSizeLabel(QSize(70,80));
    sunflowerLabel->setPixmapLabel(":/resources/jspvz/black2.png");
    sunflowerLabel->setMouseTracking(false);

    wallnutLabel = new Label(parent);
    wallnutLabel->move(m_wallnutBtn->pos());
    wallnutLabel->setFixedSize(QSize(70,80));
    wallnutLabel->setPixmapLabel(":/resources/jspvz/black2.png");
    wallnutLabel->setMouseTracking(false);

    sunflowerLabel->show();
    shootlabel->show();
    wallnutLabel->show();

    connect(m_cintor->timer,&QTimer::timeout,this,&ChoosePlantsTitllBar::on_timeout);
    connect(m_cintor,&ScreenControler::ending,this,&ChoosePlantsTitllBar::endingGame);
    connect(m_cintor,&ScreenControler::winning,this,&ChoosePlantsTitllBar::winGame);
    connect(m_cintor,&ScreenControler::SunMunApl,this,&ChoosePlantsTitllBar::addSunNum);
}

ChoosePlantsTitllBar::~ChoosePlantsTitllBar()
{
     count = 0;
     start_time = 100;
     m_start = 0;
     m_plants_num = 1;
     plantName = "";
    if(m_cintor != nullptr){
        delete m_cintor;
        m_cintor = nullptr;
    }
    if(m_shooterBtn != nullptr){
        delete m_shooterBtn;
        m_shooterBtn = nullptr;
    }
    if(m_wallnutBtn != nullptr){
        delete m_wallnutBtn;
        m_wallnutBtn = nullptr;
    }
    if(m_sunflowerBtn != nullptr){
        delete m_sunflowerBtn;
        m_sunflowerBtn = nullptr;
    }
    if(shootlabel != nullptr){
        delete shootlabel;
        shootlabel = nullptr;
    }
    if(wallnutLabel != nullptr){
        delete wallnutLabel;
        wallnutLabel = nullptr;
    }
    if(sunflowerLabel != nullptr){
        delete sunflowerLabel;
        sunflowerLabel = nullptr;
    }
    if(unClicked != nullptr){
        delete unClicked;
        unClicked = nullptr;
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<9;j++){
            if(m_labels[i][j] != nullptr){
                delete m_labels[i][j];
                m_labels[i][j] = nullptr;
            }
        }
    }
}

void ChoosePlantsTitllBar::show()
{
    m_shooterBtn->show();
    m_sunflowerBtn->show();
    m_wallnutBtn->show();
}

void ChoosePlantsTitllBar::stop()
{
    m_cintor->stopTime();
}

void ChoosePlantsTitllBar::start()
{
    m_cintor->startTime();
}

void ChoosePlantsTitllBar::addZombies(int col)
{
    m_cintor->addZombie(col);
}

void ChoosePlantsTitllBar::setAddPlant(int count)
{
    count_time = count;
}

void ChoosePlantsTitllBar::setZombieBlood(int blood)
{
    m_cintor->setZombiesBlood(blood);
}

void ChoosePlantsTitllBar::onattackPlay()
{
    //this->m_playerSc->play();
    emit doRun();
}

void ChoosePlantsTitllBar::addSunNum()
{
    FirstScreen::sun_num += SunFlower::produced;
    emit sunMumChanged();
}

void ChoosePlantsTitllBar::endingGame()
{
    emit ending();
}

void ChoosePlantsTitllBar::winGame()
{
    emit winning();
}

void ChoosePlantsTitllBar::on_timeout()
{
    if(start_time >= m_start){
        m_start++;
        return;
    }
    //qDebug()<<"kaishi";
    if(FirstScreen::sun_num >= 50 && FirstScreen::sun_num <100){
       //shooterpresslabel->move(0,-100);
       shootlabel->setMouseTracking(false);
       sunflowerLabel->setMouseTracking(true);
       wallnutLabel->setVisible(false);
       shootlabel->show();
       wallnutLabel->show();
       sunflowerLabel->hide();
    }else if(FirstScreen::sun_num < 125 && FirstScreen::sun_num >= 100){
        shootlabel->setMouseTracking(true);
        wallnutLabel->setVisible(false);
        sunflowerLabel->setMouseTracking(true);
        sunflowerLabel->hide();
        shootlabel->hide();
        wallnutLabel->show();
    }else if (FirstScreen::sun_num >= 125) {
        shootlabel->setMouseTracking(true);
        sunflowerLabel->setMouseTracking(true);
        wallnutLabel->setMouseTracking(true);
        sunflowerLabel->hide();
        shootlabel->hide();
        wallnutLabel->hide();
    }
    else {
        shootlabel->setMouseTracking(false);
        sunflowerLabel->setMouseTracking(false);
        wallnutLabel->setMouseTracking(false);
        sunflowerLabel->show();
        shootlabel->show();
        wallnutLabel->show();
    }
//    count++;
//    if(count >= count_time*100){
//        count = 1;
//    }
//    if(count % count_time == 0){
//        //this->m_plants_num ++;
//        FirstScreen::sun_num += 50;
//        emit sunMumChanged();
//    }
//    if(this->m_plants_num >= 5){
//        this->m_plants_num = 5;
//    }
//    if(this->m_plants_num > 0){
//        label->hide();
//    }else {
//        label->show();
//    }
//    numlabel->setText(QString("%1").arg(m_plants_num));
//    numlabel->show();
}


void ChoosePlantsTitllBar::on_shooterBtnRelease(QPoint point)
{
    if(plantName == ""){
        return;
    }
    //qDebug()<<point.x()<<point.y();
    for(int i=0;i<5;i++){
        for(int j=0;j<9;j++){
            if(point.x() > m_labels[i][j]->pos().x()
                    && point.x() < m_labels[i][j]->pos().x() + m_labels[i][j]->width()){
                if(point.y() > m_labels[i][j]->pos().y()
                        && point.y() < m_labels[i][j]->pos().y() + m_labels[i][j]->height()){
                    if(m_cintor->plantBlood(i,j)>0){
                    }else{
                        m_labels[i][j]->m_is_full = false;
                        m_cintor->addPlant(i,j,plantName,p);

                        if(plantName == "shooter"){//sunflower
                            FirstScreen::costSun(Shooters::m_cost);
                        }else if(plantName == "sunflower"){
                            FirstScreen::costSun(SunFlower::m_cost);
                        }else if (plantName == "wallnut") {
                            FirstScreen::costSun(WallNut::m_cost);
                        }

                        emit sunMumChanged();
                        m_labels[i][j]->m_is_full = true;
                    }
//                    if(m_cintor->shooter[i][j] == nullptr){
//                        qDebug()<<"plant0"<<plantName;
//                        m_cintor->addPlant(i,j,plantName,p);
//                        //m_plants_num --;
//                        //m_cintor->addZombie(i);
//                        qDebug()<<"plant0"<<plantName;
//                        if(plantName == "shooter"){//sunflower
//                            FirstScreen::costSun(Shooters::m_cost);
//                        }else if(plantName == "sunflower"){
//                            FirstScreen::costSun(SunFlower::m_cost);
//                        }
//                        emit sunMumChanged();
//                        m_labels[i][j]->m_is_full = true;
//                    }
//                    if(m_cintor->shooter[i][j]->m_blood <= 0 && m_labels[i][j]->m_is_full == true){
//                        m_labels[i][j]->m_is_full = false;
//                        qDebug()<<"plant"<<plantName;
//                        m_cintor->addPlant(i,j,plantName,p);
//                        //m_cintor->addZombie(i);
//                        //m_plants_num --;
//                        qDebug()<<"plant"<<plantName;
//                        if(plantName == "shooter"){//sunflower
//                            FirstScreen::costSun(Shooters::m_cost);
//                        }else if(plantName == "sunflower"){
//                            FirstScreen::costSun(SunFlower::m_cost);
//                        }
//                        emit sunMumChanged();
//                        m_labels[i][j]->m_is_full = true;
//                    }

                }
            }
        }
    }
}

void ChoosePlantsTitllBar::on_EnterLabel()
{
    qDebug()<<"enter";
}
