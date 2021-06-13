#ifndef BASICZOMBIES_H
#define BASICZOMBIES_H

#include <QWidget>
#include "basicmovie.h"
enum ZombieStyle{
    NORMAL_ZOMBIE,
    CONEHEAD_ZOMBIE
};
enum ZombieInfo{
    ATTACKING,
    DIED,
    RUNNING,
    DEFAULEINFO
};
class BasicZombies : public BasicMovie
{
    Q_OBJECT
public:
    explicit BasicZombies(QWidget *parent = nullptr);
    virtual ~BasicZombies();
    void move(const QPoint &point);
    void setZombieStyle(ZombieStyle style);
    void setFixedSize(QSize size);
    void setZombieInfo(ZombieInfo zombieInfo);
    void setPixMap(const QString &map);
signals:
    void signalIsChanged();
    void on_setBtnClicked();
public:
    ZombieStyle m_zombieStyle;
    ZombieInfo m_zombieInfo;
    //bool m_isChanged;
};

#endif // BASICZOMBIES_H
