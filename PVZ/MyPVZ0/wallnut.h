#ifndef WALLNUT_H
#define WALLNUT_H

#include <QObject>
#include "basicplants.h"
enum WallNutBlood{
    HEALTH,
    NOTHEALTH,
    BEDIED,
    NOSTYLE
};

class WallNut : public QObject
{
    Q_OBJECT
public:
    explicit WallNut(QWidget *parent = nullptr);
    ~WallNut();
    void show();
    void setCol_Id(int col,int id);
    void move(QPoint point);
    void create(QPoint point);
    void setDefaultBlood();
    void setBlood(int blood);
    void deleted();
    void subBlood(int hert);
    void setWallNutStyle(WallNutBlood style);
signals:

public slots:
    void on_timeout();
public:
    BasicPlants *m_plant = nullptr;
    int m_blood = 0;
    int hujia = 7;
    int defaultblood = 1500;
    static int m_cost;
    int m_col = -1;
    int m_id = -1;
    bool m_is_died = true;
    WallNutBlood style = NOSTYLE;
};

#endif // WALLNUT_H
