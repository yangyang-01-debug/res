#include "setbtndialog.h"
#include <QPainter>
#include <QThread>
#include <QMovie>
SetBtnDialog::SetBtnDialog(QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(316,473);
     this->setWindowFlags(Qt::FramelessWindowHint);
     closeBtn = new MyBtn(this);
     continueBtn = new MyBtn(this);
     cancelBtn = new MyBtn(this);
     title = new TitleBar(this);
     btn = new QPushButton(this);
     btn->setText("restart");
     btn->show();
     btn->move(230,50);
     quitBtn = new QPushButton(this);
     quitBtn->setText("quit");
     quitBtn->show();
     quitBtn->move(-3,50);
     connect(quitBtn,&QPushButton::clicked,this,&SetBtnDialog::onquit);
     connect(btn,&QPushButton::clicked,this,&SetBtnDialog::onBtnClicked);
     title->setTitleColor(QColor(141,63,24));//setTitleColor(QColor(141,63,24));
        title->setButtonType(ONLY_CLOSE_BUTTON);
        QString str =":/resources/MainWindow/icons/icon.png";
        title->setTitleIcon(str);
        str = "选择界面";
        title->setTitleContent(str);
    connect(title,&TitleBar::signalButtonCloseClicked,this,&SetBtnDialog::on_closeClicked);
     closeBtn->setPixMapBtn(":/resources/jspvz/closeBtn.png");
     continueBtn->setPixMapBtn(":/resources/jspvz/continueBtn.png");
     cancelBtn->setPixMapBtn(":/resources/jspvz/cancelBtn.png");

     closeBtn->setFixedSizeBtn(QSize(163,57));
     continueBtn->setFixedSizeBtn(QSize(163,57));
     cancelBtn->setFixedSizeBtn(QSize(163,57));

     closeBtn->move(QPoint(70,150));
     continueBtn->move(QPoint(70,250));
     cancelBtn->move(QPoint(70,350));

     connect(closeBtn,&MyBtn::clicked,this,&SetBtnDialog::oncloseBtn);
     connect(cancelBtn,&MyBtn::clicked,this,&SetBtnDialog::oncancelBtn);
     connect(continueBtn,&MyBtn::clicked,this,&SetBtnDialog::oncontinueBtn);
}

SetBtnDialog::~SetBtnDialog()
{/*    QMovie * = nullptr;
    QLabel *;

    TitleBar *;
    MyBtn *;
    MyBtn *;
    MyBtn *;
    QPushButton *;*/
    if(m != nullptr){
        m->stop();
        delete m;
        m = nullptr;
    }
    if(lab != nullptr){
        delete lab;
        lab = nullptr;
    }
    if(title != nullptr){
        delete title;
        title = nullptr;
    }
    if(closeBtn != nullptr){
        delete closeBtn;
        closeBtn = nullptr;
    }
    if(continueBtn != nullptr){
        delete continueBtn;
        continueBtn = nullptr;
    }
    if(cancelBtn != nullptr){
        delete cancelBtn;
        cancelBtn = nullptr;
    }
    if(btn != nullptr){
        delete btn;
        btn = nullptr;
    }
//    if(m != nullptr){
//        delete m;
//        m = nullptr;
//    }
}

void SetBtnDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/resources/jspvz/talk.png"));
}

void SetBtnDialog::onquit()
{
    lab = new QLabel(this);
    //lab.setParent(this);
    lab->setFixedSize(90,90);
    m = new QMovie(":/resources/jspvz/AjaxLoader.gif");
    lab->setMovie(m);
    m->start();
    lab->show();
    lab->move(100,250);
    //emit restart();
   //m = nullptr;
    QTimer::singleShot(2000, this,[this](){
        //emit this->restart();
        emit quit();
    });
    //emit quit();
}

void SetBtnDialog::onBtnClicked()
{
    lab = new QLabel(this);
    //lab.setParent(this);
    lab->setFixedSize(90,90);
    m = new QMovie(":/resources/jspvz/AjaxLoader.gif");
    lab->setMovie(m);
    m->start();
    lab->show();
    lab->move(100,250);
    //emit restart();
   //m = nullptr;
    QTimer::singleShot(2000, this,[this](){
        emit this->restart();
    });
}

void SetBtnDialog::oncloseBtn()
{
    emit closeBtnClicked();
}

void SetBtnDialog::oncontinueBtn()
{
    emit continueBtnClicked();
}

void SetBtnDialog::oncancelBtn()
{
    emit cancelBtnClicked();
}

void SetBtnDialog::on_closeClicked()
{
    emit cancelBtnClicked();
}
