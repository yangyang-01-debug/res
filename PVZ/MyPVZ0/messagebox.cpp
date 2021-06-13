#include "messagebox.h"
#include <QPainter>
#include <QSize>
#define BUTTON_YES ":/resources/jspvz/ButtonYes.png"
#define BUTTON_NO ":/resources/jspvz/ButtonNo.png"
#define BUTTON ":/resources/jspvz/Button.png"
#define MESSAGEBOX_BACKGROUND ":/resources/jspvz/talk.png"
MessageBox::MessageBox(QWidget *parent) : QWidget(parent)
{
    this->m_title = "提示";
    this->m_text = "提示信息";
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(400,300);
    this->m_titleBar = new TitleBar(this);
    this->m_titleBar->setButtonType(ONLY_CLOSE_BUTTON);
    this->m_titleBar->setTitleColor(QColor(141,63,24));
    MyBtn *btn1 = new MyBtn(this);
    MyBtn *btn2 = new MyBtn(this);
    btn1->setPixMapBtn(BUTTON_YES);
    btn1->setObjectName("yes");
    btn1->setFixedSizeBtn(QSize(100,50));
    btn2->setPixMapBtn(BUTTON_NO);
    btn2->setObjectName("no");
    btn2->setFixedSizeBtn(QSize(100,50));
    this->m_mylist_mybtn.push_back(btn1);
    this->m_mylist_mybtn.push_back(btn2);
    connectsToTitle();
    setstyle();
}

MessageBox::MessageBox(const QStringList namelist, QWidget *parent) : QWidget(parent)
{
    this->m_title = "提示";
    this->m_text = "提示信息";
    this->setFixedSize(400,300);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->m_titleBar = new TitleBar(this);
    this->m_titleBar->setButtonType(ONLY_CLOSE_BUTTON);
    this->m_titleBar->setTitleColor(QColor(141,63,24));
    for(int i = 0; i < namelist.length(); i ++){
        MyBtn *btn = new MyBtn(this);
        btn->setPixMapBtn(BUTTON);
        btn->setFixedSizeBtn(QSize(100,50));
        QFont f;//KaiTi STXingkai
        f.setFamily("STXingkai");
        f.setPointSize(25);
        btn->setText(namelist.at(i),f);
        btn->setObjectName(namelist.at(i));
        this->m_mylist_mybtn.push_back(btn);
    }

    connectsToTitle();
    setstyle();
}

MessageBox::~MessageBox()
{
    if(this->m_titleBar != nullptr){
        delete this->m_titleBar;
        this->m_titleBar = nullptr;
    }
    if(this->m_mylist_mybtn.isEmpty())return;
    for(int i = 0; i < this->m_mylist_mybtn.length(); i ++){
        MyBtn *btn = nullptr;
        btn = this->m_mylist_mybtn[0];
        if(btn != nullptr){
            delete btn;
            btn = nullptr;
        }
        this->m_mylist_mybtn.pop_front();
    }
}

//QString MessageBox::getReturn()
//{
//   return this->m_return;
//}

void MessageBox::setText(const QString &title, const QString &text)
{
    this->m_text = text;
    this->m_title = title;
}

void MessageBox::connectsToTitle()
{
    connect(this->m_titleBar,&TitleBar::signalButtonCloseClicked,this,&MessageBox::onButtonCloseClicked);
    for(int i = 0;i < this->m_mylist_mybtn.length(); i++){
        connect(this->m_mylist_mybtn.at(i),SIGNAL(btnclicked(QString)),this,SLOT(onButtonClicked(QString)));
    }
}

void MessageBox::setstyle()
{
    QString s;
    s=MIN_ICON;
    this->m_titleBar->setTitleIcon(s);
    s=TITLE_CONTENT;
    this->m_titleBar->setTitleContent(s);

    int sp = (this->width() - this->m_mylist_mybtn.length() *100)/(this->m_mylist_mybtn.length()+1);
    int widths = 100;
    while (sp<0){
        sp = (this->width() - this->m_mylist_mybtn.length() *widths)/(this->m_mylist_mybtn.length()+1);
        for(int i=0;i<this->m_mylist_mybtn.length();i++){
            this->m_mylist_mybtn[i]->setFixedSizeBtn(QSize(widths/2,widths/4));
        }
    }
    for(int i=0;i<this->m_mylist_mybtn.length();i++){
        this->m_mylist_mybtn[i]->move(QPoint(50+200*i,200));
    }
}

void MessageBox::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QFont f;
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(MESSAGEBOX_BACKGROUND));
    f.setFamily("STXingkai");
    f.setPixelSize(20);
    p.setFont(f);
    p.setPen(QColor(255,255,255));
    p.drawText(20,50,this->m_title);
    p.setPen(QColor(0,0,0));
    p.drawText(50,120,this->m_text);
}

void MessageBox::onButtonCloseClicked()
{
    emit this->closebox("close");
    this->close();
}

void MessageBox::onButtonClicked(const QString &str)
{
    //this->m_return = str;
    emit this->closebox(str);
    this->close();
}
