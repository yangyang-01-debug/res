#ifndef BASICMOVIE_H
#define BASICMOVIE_H

#include <QObject>
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QMetaType>
class BasicMovie : public QObject
{
    Q_OBJECT
public:
    explicit BasicMovie(QWidget *parent = nullptr);
    virtual ~BasicMovie();

    virtual void setFixedSize(const QSize &size);
    virtual void move(const QPoint &point);
    void startMovie();
    void stopMovie();
    void show();
    void hide();
    //virtual void paintEvent(QPaintEvent *);
signals:

public:
    void setPixmapLabel(const QString &mapPath);

public:
    bool m_isBeBoomed;
    QPoint m_point;
    //QPoint m_startPoint;
public:
    QLabel *m_label;
    QMovie *m_movie;
    QRect m_rect;
};

#endif // BASICMOVIE_H
