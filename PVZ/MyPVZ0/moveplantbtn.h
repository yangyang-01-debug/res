#ifndef MOVEPLANTBTN_H
#define MOVEPLANTBTN_H

#include <QWidget>
#include "basicplantsBtn.h"
class ChoosePlantsTitllBar;
class MovePlantBtn : public BasicPlantBtn
{
    Q_OBJECT
public:
    explicit MovePlantBtn(QWidget *parent = nullptr);
    MovePlantBtn(QString name,const QString &mapPath,QWidget *parent = nullptr);
    void setTextLabel(QString text,QWidget *parent);
    ~MovePlantBtn();
signals:
    void signalMousePoint(QPoint point);
private:
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

public:
    bool m_is_press = false;
    QString m_name;
private:
    QLabel *m_text = nullptr;
    Label *m_moveLabel;
    QPoint m_releasePoint;
};

#endif // MOVEPLANTBTN_H
