#include "firstscreen.h"
#include<QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QTimer>
#define BACKGROUND1 ":/resources/jspvz/background1.jpg"
#define BACKGROUND ":/resources/jspvz/001.png"
int start_set_zombies =0;
int addZombies = 1;
int start_set_zombies_time = 20;
int FirstScreen::sun_num = 50;
int alreadysetZombies =0;
FirstScreen::FirstScreen(QWidget *parent) : BasicWindow(parent)
{
    srand((unsigned)time(NULL));
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&FirstScreen::on_timeout);

    //m_timer->start(1000);
    init();
    //setBtnDialog *d = new setBtnDialog(this);
    //d->show();
}

FirstScreen::FirstScreen(int id, QList<int> list, QWidget *parent): BasicWindow(parent)
{
    this->id  = id;
    srand((unsigned)time(NULL));
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&FirstScreen::on_timeout);
    //m_timer->start(1000);
    init();
    this->m_zombielist = list;
    zombiesmun = list.length();
}

FirstScreen::~FirstScreen()
{
    //qDebug()<<"delete";
    sun_num = 50;
     start_set_zombies =0;
     addZombies = 1;
     start_set_zombies_time = 20;
    //int FirstScreen::sun_num = 50;
     alreadysetZombies =0;
    if(m_sunBckLabel != nullptr){
        delete m_sunBckLabel;
        m_sunBckLabel = nullptr;
    }
    if(m_sunNumLabel != nullptr){
        delete m_sunNumLabel;
        m_sunNumLabel = nullptr;
    }
    if(ready_plants != nullptr){
        delete ready_plants;
        ready_plants = nullptr;
    }
    if(m_timer != nullptr){
        m_timer->stop();
        delete m_timer;
        m_timer = nullptr;
    }
    if(m_player != nullptr){
        m_player->stop();
        delete m_player;
        m_player = nullptr;
    }
    if(m_readyplay != nullptr){
        delete m_readyplay;
        m_readyplay = nullptr;
    }
    if(m_play_list != nullptr){
        delete m_play_list;
        m_play_list = nullptr;
    }
    if(attackplay != nullptr){
        if(attackplay->isRunning()){
            attackplay->quit();
            attackplay->wait();
        }
        delete attackplay;
        attackplay = nullptr;
    }
    if(bar != nullptr){
        delete bar;
        bar = nullptr;
    }
}

void FirstScreen::setSize(const QSize &size)
{
    this->setFixedSize(size);
    update();
}

void FirstScreen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap map;
    map.load(this->m_mapPath);
    painter.drawPixmap(0,0,this->width(),this->height(),map);
}

void FirstScreen::setZombies(QList<int> list)
{
    this->m_zombielist = list;
    zombiesmun = list.length();
}

void FirstScreen::setPlontAddCount(int count)
{
    bar->setAddPlant(count);
}

void FirstScreen::setZombieAddCount(int count)
{
    this->basicTimeCout = count;
}

void FirstScreen::init()
{
    connect(this,&FirstScreen::cancelClose,this,&FirstScreen::oncancelClose);
    connect(this,&FirstScreen::closeWidget,this,&FirstScreen::oncloseWidget);
    connect(this,&FirstScreen::signalSetBtnClicked,this,&FirstScreen::onSetBtnClicked);
    this->setBackGround(QString("%1").arg(BACKGROUND));
    this->setFixedSize(1250,626);
    this->m_setBtn->move(QPoint(1835,30));
    this->m_setBtn->show();
    this->m_titleBar->setButtonType(MIN_BUTTON);
    emit this->m_titleBar->signalButtonMaxClicked();

    connect(this->m_titleBar,&TitleBar::signalButtonMinClicked,this,&FirstScreen::onMinClicked);
    connect(this,&FirstScreen::restore,this,&FirstScreen::onrestore);
    this->ready_plants = new QLabel(this);
    this->ready_plants->setFixedSize(255,324);
    this->ready_plants->setPixmap(QPixmap(":/resources/jspvz/PrepareGrowPlants.png"));
    this->ready_plants->move(0,-500);
    this->m_player = new QMediaPlayer(this);//WELCOM_VIDEO_PATH
    this->m_play_list = new QMediaPlaylist(this);//BUTTON_CLICKED
    QUrl url(QString("qrc%1").arg(PLAY_VIDEO_PATH));
    this->m_play_list->addMedia(url);
    //qDebug()<<"welcome:"<<url;
    //循环播放
    this->m_play_list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    this->m_player->setPlaylist(this->m_play_list);
    this->m_player->play();

    this->bar = new ChoosePlantsTitllBar(this);
    bar->show();
    connect(bar,&ChoosePlantsTitllBar::ending,this,&FirstScreen::on_endGame);
    connect(bar,&ChoosePlantsTitllBar::winning,this,&FirstScreen::on_winGame);
    connect(bar,&ChoosePlantsTitllBar::doRun,this,&FirstScreen::on_doRun);
    m_readyplay = new QMediaPlayer(this);
    m_sunBckLabel = new Label(this);
    m_sunNumLabel = new QLabel(this);
    m_sunBckLabel->setPixmapLabel(SUNBACK_PATH);
    m_sunBckLabel->setFixedSizeLabel(QSize(123,34));
    m_sunNumLabel->setFixedSize(100,34);
    m_sunBckLabel->move(QPoint(5,30));
    m_sunNumLabel->move(50,33);
    m_sunBckLabel->show();
    QFont f;
    f.setFamily("STXingkai");
    f.setPointSize(15);
    m_sunNumLabel->setFont(f);
    m_sunNumLabel->setText(QString("%1").arg(sun_num));
    m_sunNumLabel->show();
    connect(bar,&ChoosePlantsTitllBar::sunMumChanged,this,&FirstScreen::on_sunMunChanged);
}

void FirstScreen::start()
{
    m_timer->start(m_timeCount);
}

void FirstScreen::stop()
{
    this->m_timer->stop();
    this->bar->m_cintor->stopTime();
}

void FirstScreen::costSun(int mun)
{
    FirstScreen::sun_num -= mun;
}

void FirstScreen::onrestore()
{
    emit this->m_titleBar->signalButtonMaxClicked();
    m_player->play();
    m_timer->start(m_timeCount);
    bar->m_cintor->startTime();
}

void FirstScreen::onMinClicked()
{
    this->m_player->pause();
    this->m_timer->stop();
    this->bar->m_cintor->stopTime();
}

void FirstScreen::onquit()
{
    emit signalquit();
}

void FirstScreen::onrestart()
{
    emit signalRestart(id);
}

void FirstScreen::on_doRun()
{
    if(this->attackplay == nullptr){
        attackplay = new MediaPlayer();
        //connect(attackplay,&MediaPlayer::finished,attackplay,&MediaPlayer::deleteLater);
    }
    //->m_player->pause();
    //qDebug()<<"pause";
    attackplay->start();
//    if(this->pool == nullptr){
//        pool = new QThreadPool(this);
//        pool->setMaxThreadCount(4);
//    }
//       pool->start(new Mediap());

}

void FirstScreen::on_sunMunChanged()
{
    this->m_sunNumLabel->setText(QString("%1").arg(sun_num));
//    qDebug()<<"";
    this->m_sunNumLabel->show();
}

//void FirstScreen::closeEvent(QCloseEvent *)
//{

//}

void FirstScreen::on_endGame()
{
    this->bar->stop();
    m_timer->stop();
    QUrl url(QString("qrc%1").arg(ENDING_VIDEO_PATH));
    m_player->setMedia(url);
    this->m_player->play();

    Label *lb = new Label(this);
    lb->setPixmapLabel(":/resources/jspvz/black2.png");
    lb->setFixedSizeLabel(QSize(this->width(),this->height()));
    lb->move(0,0);
    lb->show();
    Label *la = new Label(this);
    //la->setFixedSize(this->width(),this->height());
    la->setFixedSizeLabel(QSize(498,439));
    la->setPixmapLabel(QString(":/resources/jspvz/ZombiesWon.png"));
    la->move(700,300);
    la->show();

    MyBtn *btn = new MyBtn(this);
    //QPushButton *btn = new QPushButton(this);
    QFont f;
    f.setFamily("STXingkai");
    f.setPointSize(15);
    QString s = "关闭";
    btn->setText(s,f);
    btn->move(QPoint(1500,800));   ;//move(1500,800);
    btn->setPixMapBtn(":/resources/jspvz/Button.png");
    btn->setFixedSizeBtn(QSize(120,50));
    btn->show();
    connect(btn,&MyBtn::clicked,[this](){this->setMessageBox(false);this->close();emit signalScClosed();});
}

void FirstScreen::onSetBtnClicked()
{
    this->m_timer->stop();
    bar->stop();
    m_player->pause();
    if(dialog == nullptr){
        dialog = new SetBtnDialog(this);
        connect(dialog,&SetBtnDialog::cancelBtnClicked,this,&FirstScreen::oncancelBtnClicked);
        connect(dialog,&SetBtnDialog::closeBtnClicked,this,&FirstScreen::oncloseBtnClicked);
        connect(dialog,&SetBtnDialog::continueBtnClicked,this,&FirstScreen::oncontinueBtnClicked);
        connect(dialog,&SetBtnDialog::restart,this,&FirstScreen::onrestart);
        connect(dialog,&SetBtnDialog::quit,this,&FirstScreen::onquit);
    }
    dialog->show();
}


void FirstScreen::oncloseBtnClicked()
{
    this->setMessageBox(true);
    dialog->close();
    this->close();
}

void FirstScreen::oncancelBtnClicked()
{
    dialog->close();
    bar->start();
    this->m_timer->start(m_timeCount);
    m_player->play();
}

void FirstScreen::oncontinueBtnClicked()
{
    dialog->close();
    bar->start();
    this->m_timer->start(m_timeCount);
    m_player->play();
}

void FirstScreen::on_timeout()
{

    start_set_zombies++;
    if(start_set_zombies <= 4){
        m_player->pause();
        QUrl url1(QString("qrc%1").arg(":/resources/jspvz/videos/sys/awooga.mp3"));
        //qDebug()<<m_readyplay->state();
        if(m_readyplay->state() == QMediaPlayer::PlayingState)return;
        m_readyplay->setMedia(url1);
        m_readyplay->play();
    }else if (start_set_zombies <= 10){
        m_player->pause();
        QUrl url1(QString("qrc%1").arg(":/resources/jspvz/videos/sys/readysetplant.mp3"));
        if(m_readyplay->state() == QMediaPlayer::PlayingState)return;
        m_readyplay->setMedia(url1);
        m_readyplay->play();
        this->ready_plants->move(800,400);
        this->ready_plants->show();
    } else {
        if(m_readyplay->state() == QMediaPlayer::PausedState
                && m_player->state() == QMediaPlayer::PlayingState){
        }else {
            m_readyplay->stop();
            m_player->play();
            this->ready_plants->move(0,-500);
        }
    }
    //qDebug()<<start_set_zombies;

//    if(this->m_attackPlay != nullptr){
//        if(this->m_player->state() == QMediaPlayer::PausedState
//                && this->m_attackPlay->state() == QMediaPlayer::StoppedState){
//            this->m_player->play();
//        }
//    }

    if(start_set_zombies <= start_set_zombies_time){
        return;
    }
    start_set_zombies = start_set_zombies_time +20;

    if(addZombies >= addZombies_times*100){
         addZombies = 0;
    }
    if(addZombies % addZombies_times == 0){
        if(m_zombielist.isEmpty()){
            return;
        }
        int col = m_zombielist.at(0);
        bar->addZombies(col);
        alreadysetZombies ++;
        m_zombielist.pop_front();
    }
    //qDebug()<<addZombies_times<<zombiesmun<<alreadysetZombies;
     if (zombiesmun - alreadysetZombies == (zombiesmun/3*2)) {
        this->addZombies_times = this->basicTimeCout/3*2;
        bar->setZombieBlood(200);
    }else if(zombiesmun - alreadysetZombies == (zombiesmun/3)){
        this->addZombies_times = this->basicTimeCout/3;
        bar->setZombieBlood(300);
    }else if(zombiesmun - alreadysetZombies == (zombiesmun/6)){
         this->addZombies_times = this->basicTimeCout/6;
    }
   // qDebug()<<bar->m_cintor->zombie[0]->defaultBlood;
    addZombies++;
}

void FirstScreen::on_winGame()
{
    if(!m_zombielist.isEmpty()){
        return;
    }
    //qDebug()<<"stop";
    this->bar->stop();
    this->m_timer->stop();
    QUrl url(QString("qrc%1").arg(WIN_VIDEO_PATH));
    m_player->setMedia(url);
    this->m_player->play();
    Label *lb = new Label(this);
    lb->setPixmapLabel(":/resources/jspvz/black2.png");
    lb->setFixedSizeLabel(QSize(this->width(),this->height()));
    lb->move(0,0);
    lb->show();
    Label *la = new Label(this);
    //la->setFixedSize(this->width(),this->height());
    la->setFixedSizeLabel(QSize(this->width()/3,this->height()/3));
    la->setPixmapLabel(QString(":/resources/jspvz/win.png"));
    la->move(700,300);
    la->show();

    MyBtn *btn = new MyBtn(this);
    //QPushButton *btn = new QPushButton(this);
    QFont f;
    f.setFamily("STXingkai");
    f.setPointSize(15);
    QString s = "关闭";
    btn->setText(s,f);
    btn->move(QPoint(1500,800));   ;//move(1500,800);
    btn->setPixMapBtn(":/resources/jspvz/Button.png");
    btn->setFixedSizeBtn(QSize(120,50));
    btn->show();
    connect(btn,&MyBtn::clicked,[this](){this->setMessageBox(false);this->close();emit signalScClosed();});
}

void FirstScreen::oncloseWidget()
{
    this->m_timer->stop();
    bar->stop();
    this->m_player->pause();
}

void FirstScreen::oncancelClose()
{
    this->m_timer->start(this->m_timeCount);
    bar->start();
    this->m_player->play();
}

void FirstScreen::winGame()
{
}

