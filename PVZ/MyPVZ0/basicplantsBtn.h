#ifndef BASICPLANT_H
#define BASICPLANT_H

#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <label.h>

#define BLACK_IMAGE ":/resources/jspvz/black2.png"
#define CHOOSE_IMAGE ":/resources/jspvz/chooseKuang.png"

class BasicPlantBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit BasicPlantBtn(QWidget *parent = nullptr);
    BasicPlantBtn(QString name,const QString &mapPath,QWidget *parent = nullptr);
    void setPixMap(const QString &mapPath);
    void setSize(const QSize &size);
    virtual ~BasicPlantBtn();
    bool is_Choosed();
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *);
signals:

public:
    QString m_plantName;
protected:
    QPixmap m_map;
    Label *m_label;
    bool m_isbeChoosed;
    bool m_isPressed;
    bool m_isClicked;
    QPoint m_pressPoint;
};

#endif // BASICPLANT_H
