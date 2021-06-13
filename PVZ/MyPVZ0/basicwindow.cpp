#include "basicwindow.h"
#include <QApplication>

BasicWindow::BasicWindow(QWidget *parent) : QDialog(parent)
{
    this->m_boxreturn = "";
    this->m_mapPath = "";
    this->m_titleBar = nullptr;
    this->mSysTrayIcon = nullptr;
    this->m_is_Message = true;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(800,600);
    init();
    connectsToTitleBar();
    //this->onButtonMaxClicked();
}

void BasicWindow::setMessage(bool fl)
{
    this->m_is_Message = fl;
}

void BasicWindow::setMessageBox(bool have)
{
    this->m_ishave = have;
}

void BasicWindow::setBackGround(const QString &mapPath)
{
    this->m_mapPath = mapPath;
    update();
}

BasicWindow::~BasicWindow()
{
    //qDebug()<<"delete";
    if(this->m_titleBar != nullptr){
        delete this->m_titleBar;
        this->m_titleBar = nullptr;
    }
    if(this->mSysTrayIcon != nullptr){
        delete this->mSysTrayIcon;
        this->mSysTrayIcon = nullptr;
    }
    if(this->m_messageBox != nullptr){
        delete this->m_messageBox;
        this->m_messageBox = nullptr;
    }
}

void BasicWindow::onButtonMinClicked()
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

void BasicWindow::onButtonMaxClicked()
{
    this->m_titleBar->saveRestoreInfo(this->pos(),this->size());
    this->showMaximized();
    emit this->maxBtnClicked();
}

void BasicWindow::onButtonCloseClicked()
{
    //qDebug()<<"close";
    emit closeWidget();
    this->close();
}

void BasicWindow::onButtonRestoreClicked()
{
    this->showNormal();
    QPoint point;
    QSize size;
    this->m_titleBar->getRestoreInfo(point,size);
    this->setFixedSize(size);
    this->move(point);
}

void BasicWindow::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
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
        delete this->mSysTrayIcon;
        this->mSysTrayIcon = nullptr;
        emit restore();
        break;
    default:
        break;
    }
}

void BasicWindow::on_setBtnClicked()
{
    emit signalSetBtnClicked();
}

void BasicWindow::init()
{
    m_setBtn = new QPushButton(this);
    m_setBtn->setText("设置");
    m_setBtn->setFixedSize(60,30);
    m_setBtn->move(3,30);
    m_setBtn->show();
    connect(m_setBtn,&QPushButton::clicked,this,&BasicWindow::on_setBtnClicked);
    this->m_titleBar = new TitleBar(this);
    QString s;
    s=MIN_ICON;
    this->m_titleBar->setTitleIcon(s);
    s=TITLE_CONTENT;
    this->m_titleBar->setTitleContent(s);
    this->m_messageBox = nullptr;
    if(this->m_messageBox == nullptr){
        //this->m_messageBox = new MessageBox();
        QStringList list;
        list.push_back("yes");
        list.push_back("no");
        this->m_messageBox = new MessageBox(list);
        this->m_messageBox->setText("提示","是否确定退出？");
    }
    this->m_messageBox->hide();
    connect(this->m_messageBox,SIGNAL(closebox(QString)),this,SLOT(oncloseBoxClicked(QString)));
}

void BasicWindow::connectsToTitleBar()
{
    connect(this->m_titleBar,&TitleBar::signalButtonCloseClicked,this,&BasicWindow::onButtonCloseClicked);
    connect(this->m_titleBar,&TitleBar::signalButtonMaxClicked,this,&BasicWindow::onButtonMaxClicked);
    connect(this->m_titleBar,&TitleBar::signalButtonMinClicked,this,&BasicWindow::onButtonMinClicked);
    connect(this->m_titleBar,&TitleBar::signalButtonRestoreClicked,this,&BasicWindow::onButtonRestoreClicked);
}

void BasicWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(this->m_mapPath != "") painter.drawPixmap(0,0,this->width(),this->height(),this->m_mapPath);
}

void BasicWindow::showEvent(QShowEvent *)
{

}

void BasicWindow::oncloseBoxClicked(QString str)
{
    this->m_boxreturn = str;
    loop.quit();
}

void BasicWindow::closeEvent(QCloseEvent *e)
{
    if(m_ishave == false){
        m_ishave = true;
        return;
    }
    if(this->m_is_Message){
        this->m_messageBox->show();
        loop.exec();
    }else {
        e->accept();
        return;
    }
    //qDebug()<<this->m_boxreturn;
    if(this->m_boxreturn == "yes"){
        QApplication::quit();
        //e->accept();
        //emit signalScClosed();
    }else if(this->m_boxreturn == "no"){
        emit cancelClose();
        e->ignore();
    }else if(this->m_boxreturn == "close"){
        emit cancelClose();
        e->ignore();
    }
}
