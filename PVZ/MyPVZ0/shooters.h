#ifndef SHOOTERS_H
#define SHOOTERS_H

#include <QObject>
#include <QList>
#include "basicpbs.h"
#include "basicplants.h"
#define shootblood_ "300"
class Shooters : public QObject
{
    Q_OBJECT
public:
    explicit Shooters(int id,QWidget *parent = nullptr);
    ~Shooters();
    void shoot();
    void setPbsStart(int i);
    void stopshoot();
    void create(QPoint point);
    void deleted();
    void move(QPoint point);
    void subBlood(int hert);
    void setPbsType(PbsType type);
    void show();
    void setCol_Id(int col,int id);
    void setDefaultBlood();
    void setBlood(int blood);

signals:

public slots:
    void on_timeout();
public:
    int defaultBlood =300;
    BasicPlants *m_plant = nullptr;
    QList<BasicPbs*> m_pbs_list;
    bool m_is_shooting = false;
    bool m_is_died = true;
    QPoint m_point = QPoint(-1,-1);
    int m_shooterId = -1;
    int m_TimeCount = 30;
    int count = 0;
    int m_blood = 30;
    int m_col = -1;
    int m_id = -1;
    static int m_cost;
};

#endif // SHOOTERS_H
