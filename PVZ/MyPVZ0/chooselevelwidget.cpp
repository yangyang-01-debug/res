#include "chooselevelwidget.h"
#include "ui_chooselevelwidget.h"

ChooseLevelWidget::ChooseLevelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseLevelWidget)
{
    ui->setupUi(this);
    srand((unsigned)time(nullptr));
    this->setWindowTitle("关卡选择");
    this->setWindowIcon(QIcon(QPixmap(":/resources/MainWindow/icons/icon.png")));
    sc = nullptr;
    m_btns_list.push_back(ui->pushButton_1);
    m_btns_list.push_back(ui->pushButton_2);
    m_btns_list.push_back(ui->pushButton_3);
    m_btns_list.push_back(ui->pushButton_4);
    m_btns_list.push_back(ui->pushButton_5);
    m_btns_list.push_back(ui->pushButton_6);
    m_btns_list.push_back(ui->pushButton_7);
    m_btns_list.push_back(ui->pushButton_8);
    m_btns_list.push_back(ui->pushButton_9);
    m_btns_list.push_back(ui->pushButton_10);
    m_btns_list.push_back(ui->pushButton_11);
    m_btns_list.push_back(ui->pushButton_12);
    for(int i=0;i<m_btns_list.length();i++){
        connect(m_btns_list.at(i),&QPushButton::clicked,this,&ChooseLevelWidget::onBtnsClicked);
    }
}

ChooseLevelWidget::~ChooseLevelWidget()
{
    delete ui;
    if(this->sc != nullptr){
        delete sc;
        sc = nullptr;
    }
}

void ChooseLevelWidget::createScreen(int id)
{
    this->hide();
    this->setVisible(false);
    QList<int> list;
    for(int i=0;i<30;i++){
       int m = rand()%5;
       list.push_back(m);
    }
    if(sc != nullptr){
        sc->setMessageBox(false);
        sc->close();
        delete sc;
        sc = nullptr;
    }
    sc = new FirstScreen(id,list,nullptr);
    connect(sc,&FirstScreen::signalScClosed,this,&ChooseLevelWidget::onScClosed);
    connect(sc,SIGNAL(signalRestart(int)),this,SLOT(onrestart(int)));
    connect(sc,&FirstScreen::signalquit,this,&ChooseLevelWidget::onquit);
    //sc->setZombieAddCount(7);
    sc->show();
    sc->start();

    /*
    FirstScreen *sc = new FirstScreen();
    QList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(0);
    sc->setZombies(list);
    sc->show();
    sc->start();*/
}

void ChooseLevelWidget::onquit()
{
    sc->hide();
    this->setVisible(true);
    this->show();
    this->id = -1;
    if( sc != nullptr){
        sc->setMessageBox(false);
        sc->close();
        delete sc;
        sc = nullptr;
    }
}

void ChooseLevelWidget::onrestart(int id)
{
    //delete sc;
    this->hide();
    this->setVisible(false);
    this->id = id;
    QTimer::singleShot(200,this,[this](){
        createScreen(this->id);
    });
}


void ChooseLevelWidget::onBtnsClicked()
{
    QObject *obj;
    obj = this->sender();
    QPushButton *btn = qobject_cast<QPushButton*>(obj);
    QString str = btn->objectName();
    if(str.indexOf("_") == -1){
        return;
    }
    QStringList list = str.split("_");
    str = list[1];
    int num = str.toInt();
    createScreen(num);
}

void ChooseLevelWidget::onScClosed()
{
    this->show();
    this->setVisible(true);
    if(sc != nullptr){
        delete sc;
        sc = nullptr;
    }
}
