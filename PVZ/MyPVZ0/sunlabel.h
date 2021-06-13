#ifndef SUNLABEL_H
#define SUNLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
class SunLabel : public QLabel
{
    Q_OBJECT
public:
    explicit SunLabel(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:
    void clicked();
public:
    bool m_is_on = false;
};

#endif // SUNLABEL_H
