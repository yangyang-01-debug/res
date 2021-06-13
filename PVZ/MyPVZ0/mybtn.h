#ifndef MYBTN_H
#define MYBTN_H

#include <QObject>
#include "label.h"
#include "button.h"
enum SizePolicy{
    Expanding,
    Fixed
};
class MyBtn : public QObject
{
    Q_OBJECT
public:
    MyBtn();
    MyBtn(QWidget *parent = nullptr);
    ~MyBtn();
    void setPixMapBtn(const QString &path);
    void setFixedSizeBtn(const QSize &size);
    void setText(const QString &text,const QFont &font);
    void setSizePolicy(const SizePolicy &Hpolicy,const SizePolicy &Vpolicy);
    void move(const QPoint &point);
    void show();
    int getWidth();
    int getHeigth();
    Button* getButton()const;
signals:
    void clicked();
    void btnclicked(const QString &name);
    void pressed();
    void released();
private slots:
    void onButtonClicked();
    void onButtonPressed();
    void onButtonReleased();
private:
    Button *m_button;
    QPoint m_point;
    Label *m_label;
};

#endif // MYBTN_H
