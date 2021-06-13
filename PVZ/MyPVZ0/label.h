#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QPixmap>
#include <QRect>
class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(QWidget *parent = nullptr);
    virtual ~Label();
    void setCol_Id(int col,int id);
    void moveLabel(QPoint point);
    void setTextLabel(const QString &text,const QFont &font);
    void setPixmapLabel(const QString &map);
    void setFixedSizeLabel(const QSize &size);
    void setDrawPoint(const QPoint &p);
    void enterEvent(QEvent *);
private:
    //void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:
    //void labelClicked();
    //void signalEnterLabel();
    void releasedLabel();
private:
    QPixmap m_map;
    QString m_text;
    QFont m_font;
    QPoint m_p;
public:
    QRect m_rect;
    int m_col = -1;
    int m_id = -1;
    bool m_is_full = false;
};

#endif // LABEL_H
