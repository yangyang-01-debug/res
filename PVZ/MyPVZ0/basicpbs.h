#ifndef BASICPBS_H
#define BASICPBS_H

#include "basicmovie.h"
//#include <QTimer>

enum PbsType{
    NORMAL_TYPE,
    FIRE_TYPE,
    ICE_TYPE
};

class BasicPbs : public BasicMovie
{
    Q_OBJECT
public:
    explicit BasicPbs(QWidget *parent = nullptr);
    void setPbsType(PbsType type);
//    void setFixedSize(const QSize &size);
    void move(const QPoint &point);
//    void startMovie();
//    void stopMovie();
//    void show();
    virtual ~BasicPbs();
private slots:
    void on_timeout();
private:
    //void setPixmapLabel(const QString &mapPath);
public:
    int m_hert = 0;
    int m_basichert = 10;
    int m_speed = 50;
    bool is_shooted;
    int m_len;
    PbsType m_Pbstype;
    //QPoint m_leftTop;
    //bool m_isBeBoomed;
    QRect m_rect;
private:
    //QTimer *m_timer;
   // QLabel *m_label;
   // QMovie *m_movie;
   // QRect m_rect;
};

#endif // BASICPBS_H
