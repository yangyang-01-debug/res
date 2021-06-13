#include "mediaplayer.h"
#include <QDebug>
MediaPlayer::MediaPlayer(QObject *parent) : QThread(parent)
{
    //setAutoDelete(true);//设置线程池执行完任务后自动删除本对象
}

void MediaPlayer::run()
{ 
//    qDebug()<<"play`";
//    if(p == nullptr){
//        qDebug()<<"new player";
//        QUrl url(QString("qrc%1").arg(":/resources/jspvz/videos/sys/splat1.mp3"));
//        //p = new QMediaPlayer();
//        p = new Plater(this);
//        p->setMedia(url);
//    }
    QUrl url(QString("qrc%1").arg(":/resources/jspvz/videos/sys/splat1.mp3"));
    //p = new QMediaPlayer();
//    p = new Plater();
//    p->setMedia(url);
//    p->play();
    Plater p;
    p.setMedia(url);
    p.play();
    msleep(300);
}

MediaPlayer::~MediaPlayer()
{
   // qDebug()<<"deleter";
}

Plater::Plater(QObject *parent) : QMediaPlayer(parent)
{
//qDebug()<<"player delete";
}

Plater::~Plater()
{
    //qDebug()<<"player delete";
}

//Mediap::Mediap()
//{
//    setAutoDelete(true);//设置线程池执行完任务后自动删除本对象
//}

//void Mediap::run()
//{
//    QUrl url(QString("qrc%1").arg(":/resources/jspvz/videos/sys/splat1.mp3"));
//    //p = new QMediaPlayer();
////    p = new Plater();
////    p->setMedia(url);
////    p->play();
//    Plater p;
//    p.setMedia(url);
//    p.play();
//   //msleep(300);
//   // QThread::msleep(300);
//}

//Mediap::~Mediap()
//{

//}
