#ifndef CHOOSEPLANTSTITLLBAR_H
#define CHOOSEPLANTSTITLLBAR_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include "label.h"
#include <QList>
#include "firstscreen.h"
#include "moveplantbtn.h"
#include "screencontroler.h"
#include <QThread>
//#define ATTACKPath ":/resources/jspvz/videos/sys/splat1.mp3"

class ChoosePlantsTitllBar : public QWidget
{
    Q_OBJECT
public:
    explicit ChoosePlantsTitllBar(QWidget *parent = nullptr);
    ~ChoosePlantsTitllBar();
    void show();
    void stop();
    void start();
    void addZombies(int col);
    void setAddPlant(int count);
    void setZombieBlood(int blood);
signals:
    void doRun();
    void ending();
    void winning();
    void sunMumChanged();
public slots:
    void onattackPlay();
    void addSunNum();
    void on_timeout();
    void on_shooterBtnRelease(QPoint point);
    void on_EnterLabel();
    void endingGame();
    void winGame();
public:
    int count_time = 100;
    static int m_plants_num;
    ScreenControler *m_cintor;

    MovePlantBtn *m_shooterBtn;
    MovePlantBtn *m_sunflowerBtn;
    MovePlantBtn *m_wallnutBtn = nullptr;

    //QLabel *numlabel;
    Label* m_labels[5][9];
    QWidget *p =nullptr;

    Label *shootlabel;
    Label *sunflowerLabel;
    Label *wallnutLabel = nullptr;


    static QString plantName;
    QLabel *unClicked = nullptr;
//    MediaPlayer *m_playerSc;
//    QThread *thread;
   // QMediaPlayer *m_playerSc;
//    QLabel *shooterpresslabel;
//    QLabel *sunflowerpresslabel;
};

#endif // CHOOSEPLANTSTITLLBAR_H
