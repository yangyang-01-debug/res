#ifndef SETBTNDIALOG_H
#define SETBTNDIALOG_H

#include <QDialog>
#include "mybtn.h"
#include "titlebar.h"
class SetBtnDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SetBtnDialog(QWidget *parent = nullptr);
    ~SetBtnDialog();
    void paintEvent(QPaintEvent *);
signals:
    void  closeBtnClicked();
    void continueBtnClicked();
    void cancelBtnClicked();
    void restart();
    void quit();
private slots:
    void onquit();
    void onBtnClicked();
    void  oncloseBtn();
    void oncontinueBtn();
    void oncancelBtn();
    void on_closeClicked();
private:
    QMovie *m = nullptr;
    QLabel *lab;

    TitleBar *title;
    MyBtn *closeBtn;
    MyBtn *continueBtn;
    MyBtn *cancelBtn;
    QPushButton *btn;
    QPushButton *quitBtn = nullptr;
};

#endif // SETBTNDIALOG_H
