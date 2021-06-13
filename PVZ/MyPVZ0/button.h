#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QPixmap>
class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent = nullptr);
    ~Button();
    void setPixmapBtn(const QString &path);
    void setTextBtn(const QString &text,const QFont &font);
private:
    void paintEvent(QPaintEvent *);
signals:

private:
    QPixmap m_map;
    QFont m_font;
    QString m_text;
};

#endif // BUTTON_H
