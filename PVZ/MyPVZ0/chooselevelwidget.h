#ifndef CHOOSELEVELWIDGET_H
#define CHOOSELEVELWIDGET_H

#include <QWidget>
#include <QList>
#include "firstscreen.h"
#include <QPushButton>
namespace Ui {
class ChooseLevelWidget;
}

class ChooseLevelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseLevelWidget(QWidget *parent = nullptr);
    ~ChooseLevelWidget();
    void createScreen(int id);
public slots:
    void onquit();
    void onrestart(int id);
    void onBtnsClicked();
    void onScClosed();
private:
    Ui::ChooseLevelWidget *ui;
    QList<QPushButton*> m_btns_list;
    FirstScreen *sc = nullptr;
    int id =-1;
};

#endif // CHOOSELEVELWIDGET_H
