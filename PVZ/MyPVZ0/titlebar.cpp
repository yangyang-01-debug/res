#include "titlebar.h"
#include <QHBoxLayout>
#include <QDebug>

#define BUTTON_WIDTH 27
#define BUTTON_HEIGTH 27

#define TITLE_HEIGHT 27

QPushButton *TitleBar::getBtn(QWidget *parent, int w, int h, QString name)
{
    QPushButton *btn = new QPushButton(parent);
//    btn->setStyleSheet("{border:none}");
//    btn->setFlat(true);
    btn->setFixedSize(w,h);
    btn->setObjectName(name);
//    btn->setText(name.mid(6));
    return btn;
}

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    this->m_isPressed = false;
    this->m_buttonType = MIN_MAX_BUTTON;//69,144,95
    this->m_titleBarColor = QColor(90,187,123);
    initControl();//初始化控件
    initConnections();//连接信号与槽
    loadStyleSheet("Title");//加载样式表
}

TitleBar::~TitleBar()
{

}

void TitleBar::setTitleColor(const QColor &color)
{
    this->m_titleBarColor = color;
    this->update();
}

void TitleBar::setTitleIcon(QString &filepath)
{   //设置标题栏图标
    QPixmap icon(filepath);
    this->m_pIcon->setFixedSize(icon.size());
    this->m_pIcon->setPixmap(icon);
    this->m_pIcon->show();
}

void TitleBar::setTitleContent(QString &titlecontent)
{   //设置标题栏内容
    this->m_pTitleContent->setText(titlecontent);
    this->m_titleContent = titlecontent;
    this->m_pTitleContent->show();
}

void TitleBar::setTitleWidth(int width)
{  //设置标题栏长度
    this->setFixedWidth(width);
}

void TitleBar::setButtonType(ButtonType type)
{   //设置按钮类型
    this->m_buttonType = type;
    switch (type) {
    case MIN_BUTTON:{
        this->m_pButtonMin->setVisible(true);
        this->m_pButtonClose->setVisible(true);
        this->m_pButtonMax->setVisible(false);
        this->m_pButtonRestore->setVisible(false);
        break;
    }
    case MIN_MAX_BUTTON:{
        this->m_pButtonMin->setVisible(true);
        this->m_pButtonClose->setVisible(true);
        this->m_pButtonMax->setVisible(true);
        this->m_pButtonRestore->setVisible(false);
        break;
    }
    case ONLY_CLOSE_BUTTON:{
        this->m_pButtonMin->setVisible(false);
        this->m_pButtonClose->setVisible(true);
        this->m_pButtonMax->setVisible(false);
        this->m_pButtonRestore->setVisible(false);
        break;
    }
    default:
        break;
    }
}

void TitleBar::saveRestoreInfo(const QPoint &point, const QSize &size)
{
    this->m_restorPos = point;
    this->m_restoreSize = size;
}

void TitleBar::getRestoreInfo(QPoint &point, QSize &size)
{
    point = this->m_restorPos;
    size = this->m_restoreSize;
}

void TitleBar::paintEvent(QPaintEvent *)
{   //绘图事件

    //设置背景颜色
    QPainter painter(this);
    QBrush bruch(Qt::SolidPattern);     // 画刷
    bruch.setColor(this->m_titleBarColor);
    painter.setBrush(bruch);
//    QPainterPath painterpath;//绘图路径
//    painterpath.setFillRule(Qt::WindingFill);//设置填充规则
//    //添加圆角矩形
//    QRect r(0,0,this->width(),this->height());
//    painterpath.addRoundedRect(r,3,3);
//    //设置渲染               平滑
//    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);
        //添加圆角矩形
    //painter.drawRoundedRect(QRect(0,0,this->width(),this->height()),3,3);
    painter.drawRect(QRect(-1,-1,this->width() + 1,this->height() + 1));
    if(this->width() != this->parentWidget()->width()){
        //窗口与父窗口长度不一致（最大化最小化）
        this->setFixedWidth(this->parentWidget()->width());
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug()<<"title mouseMoveEvent";
    if( !this->m_isPressed ){
        return QWidget::mouseMoveEvent(event);
    }
    //存在最大最小化
    if( this->m_buttonType == MIN_MAX_BUTTON ){
//        if(!this->m_pButtonMax->isVisible()){//最大化时先变小再移动
//            onButtonRestoreClicked();
//        }
        return QWidget::mouseMoveEvent(event);
    }else if( this->m_buttonType == MIN_BUTTON ){
        return QWidget::mouseMoveEvent(event);
    }

    QPoint movepoint = event->globalPos() - this->m_startMovePos;
    QPoint pos = this->parentWidget()->pos();
    this->m_startMovePos = event->globalPos();
    this->parentWidget()->move(pos.x() + movepoint.x(),pos.y() + movepoint.y());

    return QWidget::mouseMoveEvent(event);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<"title mousePressEvent";

    this->m_isPressed = true;
    this->m_startMovePos = event->globalPos();
    return QWidget::mousePressEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug()<<"title mouseReleaseEvent";

    this->m_isPressed = false;
    return QWidget::mouseReleaseEvent(event);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{   /*//鼠标双击事件(双击标题栏进行最大化最小化操作)
    if( this->m_buttonType == MIN_MAX_BUTTON ){
        if( this->m_pButtonMax->isVisible() ){//最大可见
            onButtonMaxClicked();
        }else {//最大不可见
            onButtonRestoreClicked();
        }
    }*/
    return QWidget::mouseDoubleClickEvent(event);
}

void TitleBar::initControl()
{   //初始化控件

    this->m_pButtonClose = TitleBar::getBtn(this,BUTTON_WIDTH,BUTTON_HEIGTH,"ButtonClose");
    this->m_pButtonMax = TitleBar::getBtn(this,BUTTON_WIDTH,BUTTON_HEIGTH,"ButtonMax");
    this->m_pButtonMin = TitleBar::getBtn(this,BUTTON_WIDTH,BUTTON_HEIGTH,"ButtonMin");
    this->m_pButtonRestore = TitleBar::getBtn(this,BUTTON_WIDTH,BUTTON_HEIGTH,"ButtonRestore");

    this->m_pTitleContent = new QLabel(this);
    this->m_pIcon = new QLabel(this);
    this->m_pTitleContent->setObjectName("TitleContent");

    QHBoxLayout *mylayout = new QHBoxLayout(this);
    //图标
    mylayout->addWidget(this->m_pIcon);
    mylayout->addWidget(this->m_pTitleContent);
    //按钮
    mylayout->addWidget(this->m_pButtonMin);
    mylayout->addWidget(this->m_pButtonMax);
    mylayout->addWidget(this->m_pButtonRestore);
    mylayout->addWidget(this->m_pButtonClose);
    //设置布局   设置布局的位置  //左侧，右侧，上方，下方
    mylayout->setContentsMargins(5,0,0,0);
    mylayout->setSpacing(0);//设置布局中的控件之间的间隙

    //设置尺寸策略水平拉伸垂直不变
    this->m_pTitleContent->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    this->setFixedHeight(TITLE_HEIGHT);
    this->setWindowFlags(Qt::FramelessWindowHint);//设置无边框窗体

    this->setButtonType(this->m_buttonType);//设置按钮格式
}

void TitleBar::initConnections()
{   //连接信号与槽
    connect(this->m_pButtonMin,&QPushButton::clicked,this,&TitleBar::onButtonMinClicked);
    connect(this->m_pButtonMax,&QPushButton::clicked,this,&TitleBar::onButtonMaxClicked);
    connect(this->m_pButtonRestore,&QPushButton::clicked,this,&TitleBar::onButtonRestoreClicked);
    connect(this->m_pButtonClose,&QPushButton::clicked,this,&TitleBar::onButtonCloseClicked);
}

void TitleBar::loadStyleSheet(const QString &sheetName)
{   //加载样式表
    QFile file(":resources/QSS/"+sheetName+".css");
    if(file.open(QFile::ReadOnly)){
        QString styleSheet = this->styleSheet();
        styleSheet += QString(file.readAll());
        this->setStyleSheet(styleSheet);
    }else{
        QMessageBox::information(this,"警告",QString("文件打开失败").arg(file.fileName()));
    }
    file.close();
}

void TitleBar::onButtonMinClicked()
{   //最小化按钮
    emit this->signalButtonMinClicked();
}

void TitleBar::onButtonMaxClicked()
{   //最大化按钮
    this->m_pButtonMax->setVisible(false);
    this->m_pButtonRestore->setVisible(true);
    emit this->signalButtonMaxClicked();
}

void TitleBar::onButtonRestoreClicked()
{   //最大化还原
    this->m_pButtonMax->setVisible(true);
    this->m_pButtonRestore->setVisible(false);
    emit this->signalButtonRestoreClicked();
}

void TitleBar::onButtonCloseClicked()
{   //关闭按钮
    emit this->signalButtonCloseClicked();
}





















