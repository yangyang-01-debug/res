#ifndef ZOMBIES_H
#define ZOMBIES_H

#include <QObject>
#include "basiczombies.h"

#define zombieblood_ "100"
#define zombiehert_ "10"
class Zombies : public QObject
{
    Q_OBJECT
public:
    explicit Zombies(int id,QWidget *parent = nullptr);
    ~Zombies();
    void setDefaultBlood();
    void show();
    void create(QPoint point);
    void deleted();
    void setCol(int col);
    void move(QPoint point);
    void setZombiesInfo(ZombieInfo info);
    void setBlood(int blood);
signals:

public slots:
    void on_timeout();
public:
    BasicZombies *m_zombie;
    bool m_is_died = true;
    int m_blood;
    int m_hert;
    int m_id;
    int m_col = -1;
    int m_attackCount = 0;
    int m_attackTimeCount = 20;
public:
    int defaultBlood = 100;
    int dieCount = 0;
    int dieTimeCount = 30;
    int speed = 2;
    int speedCount = 0;
    int speedTimeCount = 1;
};

#endif // ZOMBIES_H
