#ifndef SCREENCONTROLER_H
#define SCREENCONTROLER_H

#include <QObject>
#include <QPoint>
#include <QTimer>

#include "shooters.h"
#include "zombies.h"
#include "sunflower.h"
#include "wallnut.h"
#define zombie_num 30
class FirstScreen;
class ScreenControler : public QObject
{
    Q_OBJECT
public:
    explicit ScreenControler(QWidget *parent = nullptr);
    ~ScreenControler();
    QPoint getPoint(int col,int id);
    void addPlant(int col ,int id,QString name,QWidget *parent = nullptr);
    void deletePlant(int col,int id);
    void addZombie(int col);
    void startTime();
    void stopTime();
    int shooterCost();
    int sunFlowerCost();
    int plantBlood(int i,int j);
    int plantCost();
    void setZombiesBlood(int blood);
signals:
    void ending();
    void winning();
    void SunMunApl();
    void attackZombie();
public slots:
    void on_timeOut();
    void on_getSunNum();
public:
    QTimer *timer;
   // QTimer *timer2;
    //y -60
    int point_col_H[9] = {350,520,680,850,1020,1180,1350,1510,1700};
    int point_row_V[5] = {150,320,500,680,870};

    int plantId = 0;
    WallNut* wallnut[5][9];
    Shooters* shooter[5][9];
    SunFlower* sunflower[5][9];
    Zombies *zombie[zombie_num];
};

#endif // SCREENCONTROLER_H
