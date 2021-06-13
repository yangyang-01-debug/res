#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QThread>
#include <QThreadPool>
#include <QRunnable>
#include <QMediaPlayer>
class Plater : public QMediaPlayer{
    Q_OBJECT
public:
    Plater(QObject *parent = nullptr);
    ~Plater();
};
//class Mediap : public QRunnable{
//    Q_OBJECT
//public:
//    Mediap();
//    void run();
//    ~Mediap();
//private:
//    //Plater p;
//};


class MediaPlayer : public QThread
{
    Q_OBJECT
public:
    explicit MediaPlayer(QObject *parent = nullptr);
    void run();
    ~MediaPlayer();

signals:

private:
    //QMediaPlayer *p = nullptr;
    Plater *p = nullptr;
};



#endif // MEDIAPLAYER_H
