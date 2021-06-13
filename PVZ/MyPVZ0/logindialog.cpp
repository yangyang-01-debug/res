#include "logindialog.h"
#include "ui_logindialog.h"
#include "firstscreen.h"
#include "chooselevelwidget.h"
int LoginDialog::m_timer_count = 50;
bool LoginDialog::m_is_connected = false;
float LoginDialog::m_progressBar_value = 0.0;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    init();
    connectsToTitleBar();
}

LoginDialog::~LoginDialog()
{
    //qDebug()<<"delete";
    if(this->m_player != nullptr){
        this->m_player->stop();
        delete this->m_player;
        this->m_player = nullptr;
    }
    if(this->m_play_list != nullptr){
        delete this->m_play_list;
        this->m_play_list = nullptr;
    }
    if(this->m_titleBar != nullptr){
        delete this->m_titleBar;
        this->m_titleBar = nullptr;
    }
    if(this->m_timer != nullptr){
        delete this->m_timer;
        this->m_timer = nullptr;
    }
    if(this->m_btn != nullptr){
        delete this->m_btn;
        this->m_btn = nullptr;
    }
    delete ui;
}

void LoginDialog::do_timeout()
{
    this->m_progressBar_value ++;
    if(this->m_progressBar_value <= 100 && this->m_progressBar_value >= 0){
       if(this->m_is_connected == true){
           this->m_timer_count = 10;
       }
       ui->progressBar->setValue(this->m_progressBar_value);
    }else {
       this->m_timer->stop();
       ui->progressBar->setVisible(false);
       //.....进入正式界面
       //this->m_player->stop();
       this->m_btn = new MyBtn(this);
       connect(this->m_btn,&MyBtn::clicked,this,&LoginDialog::onButtonStartGameClicked);
       this->m_btn->setPixMapBtn(START_GAME);
       this->m_btn->setFixedSizeBtn(QSize(this->width()/5,this->height()/12));
       this->m_btn->move(QPoint((this->width()-this->m_btn->getWidth())/2,this->height() * 4 / 5));
       this->m_btn->show();
    }
}

void LoginDialog::onButtonStartGameClicked()
{
    this->m_player->stop();
    this->m_is_Message = false;
    ChooseLevelWidget *w0 = new ChooseLevelWidget();
    w0->show();
    this->close();
}

void LoginDialog::oncloseBoxClicked(QString str)
{
    this->m_boxreturn = str;
    loop.quit();
}

void LoginDialog::onButtonMinClicked()
{
    // 判断当前窗体,是不是工具 ,
    // 如果是的话 , 就表示 当前窗体 有工具风格 , 就进行 隐藏
    // 如果不是 ,就 进行最小化
    if (Qt::Tool == (windowFlags() & Qt::Tool))
    {
        this->hide();
    }
    else
    {
        this->showMinimized();
    }

    this->m_player->pause();

    //新建QSystemTrayIcon对象
    mSysTrayIcon = new QSystemTrayIcon(this);
    connect(this->mSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason))
            ,this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    //新建托盘要显示的icon
    QIcon icon = QIcon(MIN_ICON);
    //将icon设到QSystemTrayIcon对象中
    mSysTrayIcon->setIcon(icon);
    //当鼠标移动到托盘上的图标时，会显示此处设置的内容
    mSysTrayIcon->setToolTip("植物大战僵尸");
    //在系统托盘显示此对象
    mSysTrayIcon->show();
}

void LoginDialog::onButtonMaxClicked()
{
    this->m_titleBar->saveRestoreInfo(this->pos(),this->size());
    this->showMaximized();
}

void LoginDialog::onButtonCloseClicked()
{
    this->close();
}

void LoginDialog::onButtonRestoreClicked()
{
    this->showNormal();
    QPoint point;
    QSize size;
    this->m_titleBar->getRestoreInfo(point,size);
    this->setFixedSize(size);
    this->move(point);
}

void LoginDialog::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::Trigger:
        //单击托盘图标
        break;
    case QSystemTrayIcon::DoubleClick:
        //双击托盘图标
        //双击后显示主程序窗口
        this->showNormal();
        this->show();
        this->m_player->play();
        delete this->mSysTrayIcon;
        this->mSysTrayIcon = nullptr;
        break;
    default:
        break;
    }
}

void LoginDialog::init()
{
    this->m_titleBar = new TitleBar(this);
    //this->m_titleBar->setButtonType(ONLY_CLOSE_BUTTON);

    this->m_player = new QMediaPlayer(this);//WELCOM_VIDEO_PATH
    this->m_play_list = new QMediaPlaylist(this);//BUTTON_CLICKED
    QUrl url(QString("qrc%1").arg(WELCOM_VIDEO_PATH));
    this->m_play_list->addMedia(url);
    //qDebug()<<"welcome:"<<url;
    //循环播放
    this->m_play_list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    this->m_player->setPlaylist(this->m_play_list);
    //this->m_player->play();

    this->m_timer = new QTimer(this);
    connect(this->m_timer,&QTimer::timeout,this,&LoginDialog::do_timeout);
    this->m_timer->start(this->m_timer_count);

    this->m_btn = nullptr;
    this->m_is_Message = true;
    this->m_messageBox = new MessageBox(this);
    this->m_messageBox->setText("提示","是否确定退出？");
    this->m_messageBox->hide();
    connect(this->m_messageBox,SIGNAL(closebox(QString)),this,SLOT(oncloseBoxClicked(QString)));
}

void LoginDialog::connectsToTitleBar()
{
    connect(this->m_titleBar,&TitleBar::signalButtonCloseClicked,this,&LoginDialog::onButtonCloseClicked);
    connect(this->m_titleBar,&TitleBar::signalButtonMaxClicked,this,&LoginDialog::onButtonMaxClicked);
    connect(this->m_titleBar,&TitleBar::signalButtonMinClicked,this,&LoginDialog::onButtonMinClicked);
    connect(this->m_titleBar,&TitleBar::signalButtonRestoreClicked,this,&LoginDialog::onButtonRestoreClicked);
}

void LoginDialog::paintEvent(QPaintEvent *)
{
    if(this->m_messageBox != nullptr){
        this->m_messageBox->move(QPoint((this->width()-this->m_messageBox->width())/2,
                                 (this->height()-this->m_messageBox->height())/2));
    }

    //画背景
    QPainter paint(this);
    //paint.drawRect(QRect(0,0,this->width(),this->height()));
    paint.drawPixmap(0,0,this->width(),this->height(),QPixmap(WELCOME_BACKGROUND));

    ui->progressBar->setFixedSize(this->width(),10);
    ui->progressBar->move(0,this->height() - ui->progressBar->height());

    if(this->m_btn != nullptr){
        //this->m_btn->setPixmapBtn(START_GAME);//800*600
        //this->m_btn->setFixedSize(this->width()/5,this->height()/12);
        this->m_btn->setFixedSizeBtn(QSize(this->width()/5,this->height()/12));
        //this->m_btn->move();
        this->m_btn->move(QPoint((this->width()-this->m_btn->getWidth())/2,this->height() * 4 / 5));
        this->m_btn->show();
    }
}

void LoginDialog::showEvent(QShowEvent *event)
{
    this->m_player->play();
    event->accept();
}

void LoginDialog::closeEvent(QCloseEvent *event)
{
    //qDebug()<<"use event";
    this->m_player->stop();

    if(this->m_is_Message){
        this->m_messageBox->show();
        loop.exec();
    }else {
        event->accept();
        return;
    }
    //qDebug()<<this->m_boxreturn;
    if(this->m_boxreturn == "yes"){
        QApplication::quit();
    }else if(this->m_boxreturn == "no"){
        event->ignore();
        this->m_player->play();
    }else if(this->m_boxreturn == "close"){
        event->ignore();
        this->m_player->play();
    }

//    QMessageBox msgBox;
//    msgBox.setWindowTitle("提示信息");
//    msgBox.setText("提示");
//    msgBox.setInformativeText("确定退出?");
//    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
//    msgBox.setDefaultButton(QMessageBox::No);
//    int ret = msgBox.exec();
//    if(ret == QMessageBox::Yes){
//        QApplication::quit();
//    }else {
//        event->ignore();
//    }
}
