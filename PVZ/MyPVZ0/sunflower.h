#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include <QTimer>
#include <QWidget>
#include "mytimer.h"
#include "sunlabel.h"
#include "basicplants.h"
#define SUNNUM 5
#define SUN_PATH ":/resources/jspvz/images/plants/SunFlower/Sun47.gif"
class SunFlower : public QObject
{
    Q_OBJECT
public:
    explicit SunFlower(int id,QWidget *parent = nullptr);
    ~SunFlower();
    void show();
    void setCol_Id(int col,int id);
    void move(QPoint point);
    void moveToHide(QPoint point);
    void create(QPoint point);
    void setDefaultBlood();
    void setBlood(int blood);
    void deleted();
    void subBlood(int hert);
signals:
    void getSunNum();
public slots:
    void on_timeout();
    void onSunClicked();
public:
    QMovie *m_sunMovie;
    SunLabel* m_sunlabels[SUNNUM];
    SunLabel *m_moveSun;
    MyTimer *m_timer;
    BasicPlants *m_plant;
    bool m_is_died = true;
    int m_blood = 150;
    static int m_cost ;
    static int produced;
    static int timerid;
    int m_col = -1;
    int m_id = -1;
    int m_plantid = -1;
private:
    //QPoint startMovePoint;
    int defaultblood = 150;
    QObject *obj;
    SunLabel *l;
    bool isMoveing = false;
};

#endif // SUNFLOWER_H
